#include "Core/Locale/LocaleManager.hpp"
#include "Core/Locale/Locale.hpp"

namespace Core
{
	LocaleManager::LocaleManager() :
		_packageENG(),
		_packageLOC()
	{}

	void LocaleManager::Load()
	{
		_packageENG.Load();
		_packageLOC.Load(_locale);
	}

	bool LocaleManager::SetLocale(const std::string& a_locale)
	{
		if (a_locale.empty()) {
			auto setting = RE::GetINISetting("sLanguage:General");
			if (setting) {
				auto u8Language = setting->GetString();
				auto u16Language = stl::utf8_to_utf16(u8Language);
				_locale = u16Language.value_or(_localeDefault);
			}

			return false;
		}

		auto locale = stl::utf8_to_utf16(a_locale);
		_locale = locale.value_or(_localeDefault);

		return true;
	}

	std::string LocaleManager::Translate(const std::string& a_key)
	{
		if (!a_key.empty() && a_key[0] == '$') {
			return GetLocalization(a_key);
		}

		return a_key;
	}

	void LocaleManager::Dump()
	{
		auto& package = GetLocalePackage();
		package.Dump();
	}

	std::wstring LocaleManager::GetLocalization(const std::wstring& a_key)
	{
		return GetLocalizationImpl(a_key);
	}

	std::string LocaleManager::GetLocalization(const std::string& a_key)
	{
		auto wstr = stl::utf8_to_utf16(a_key);
		if (wstr) {
			auto locale = GetLocalizationImpl(wstr.value());
			auto str = stl::utf16_to_utf8(locale);
			return str.value_or(a_key);
		}

		return a_key;
	}

	LocalePackage& LocaleManager::GetLocalePackage()
	{
		return _packageLOC.empty() ? _packageENG : _packageLOC;
	}

	std::wstring LocaleManager::GetLocalizationImpl(const std::wstring& a_key)
	{
		if (a_key.empty() || a_key[0] != L'$')
			return a_key;

		auto sanitizedKey = Locale::SanitizeKey(a_key);
		if (!sanitizedKey)
			return a_key;

		auto localization = FindLocalization(*sanitizedKey);
		if (!localization)
			return a_key;

		std::stack<size_type> stack;
		std::queue<std::wstring> queue;
		if (!GetNestedLocalizations(a_key, stack, queue))
			return *localization;

		while (!stack.empty()) {
			stack.pop();
		}

		InsertLocalizations(*localization, stack, queue);
		return *localization;
	}

	std::optional<std::wstring> LocaleManager::FindLocalization(const std::wstring& a_key)
	{
		auto& package = GetLocalePackage();
		auto item = package.FindItem(a_key);
		if (!item) {
			auto key = stl::utf16_to_utf8(a_key);
			spdlog::info("Key not found: {}", key.value_or(""));
			if (&package != &_packageENG) {
				item = _packageENG.FindItem(a_key);
				if (!item) {
					return std::nullopt;
				}
			}
		}

		return item;
	}

	bool LocaleManager::GetNestedLocalizations(
		const std::wstring& a_key,
		std::stack<size_type>& a_stack,
		std::queue<std::wstring>& a_queue)
	{
		for (size_type pos = 0; pos < a_key.size(); ++pos) {
			switch (a_key[pos]) {
				case L'{':
					a_stack.push(pos);
					break;
				case L'}': {
					switch (a_stack.size()) {
						case 0:
							return false;
						case 1: {
							size_type last = a_stack.top();
							a_stack.pop();
							auto off = last + 1;
							auto count = pos - last - 1;
							if (count == 0) {
								return false;  // nothing to replace {} with
							}
							auto subStr = a_key.substr(off, count);
							auto locale = GetLocalizationImpl(subStr);
							a_queue.push(locale);
						} break;
						default:
							a_stack.pop();
					} break;
				}
			}
		}

		return true;
	}

	bool LocaleManager::InsertLocalizations(
		std::wstring& a_localization,
		std::stack<size_type>& a_stack,
		std::queue<std::wstring>& a_queue)
	{
		for (size_type pos = 0; pos < a_localization.size(); ++pos) {
			switch (a_localization[pos]) {
				case L'{':
					a_stack.push(pos);
					break;
				case L'}': {
					if (a_stack.empty() || a_queue.empty())
						return false;

					size_type beg = a_stack.top();
					a_stack.pop();
					auto& subStr = a_queue.front();
					a_queue.pop();

					a_localization.replace(beg, pos - beg + 1, subStr);
					pos = beg;
				} break;
			}
		}

		return true;
	}
}
