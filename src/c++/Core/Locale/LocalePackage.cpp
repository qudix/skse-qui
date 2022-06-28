#include "Core/Locale/LocalePackage.hpp"
#include "Core/Locale/Locale.hpp"

#include <codecvt>

namespace Core
{
	const fs::path LOCALE_PATH{ "data/interface/translations" };

	constexpr wchar_t REGEX_PREFIX[]{ L".*_" };
	constexpr wchar_t REGEX_POSTFIX[]{ L"\\.txt$" };
	constexpr auto	  REGEX_FLAGS{ std::regex::grep | std::regex::icase };

	constexpr auto	  CVT_MODE = std::codecvt_mode(std::little_endian | std::consume_header);

	void LocalePackage::Load()
	{
		_items.clear();

		std::wstring pattern(REGEX_PREFIX);
		pattern += _language;
		pattern += REGEX_POSTFIX;
		_regex.assign(pattern, REGEX_FLAGS);

		LoadFiles();
	}

	void LocalePackage::Load(const std::wstring& a_lang)
	{
		if (_language != a_lang) {
			_language = a_lang;
			Load();
		}
	}

	std::optional<std::wstring> LocalePackage::FindItem(const std::wstring& a_key)
	{
		auto it = _items.find(a_key);
		if (it != _items.end())
			return it->second;

		return std::nullopt;
	}

	void LocalePackage::Dump()
	{
		spdlog::info(L"[Locale: {}]", _language);
		for (auto& [key, value] : _items) {
			spdlog::info(L"  > {} : {}", key, value);
		}
	}

	void LocalePackage::LoadFiles()
	{
		std::error_code err;
		if (!fs::exists(LOCALE_PATH, err))
			return;

		fs::path fileName;
		for (auto& dir : fs::directory_iterator(LOCALE_PATH)) {
			fileName = dir.path().filename();
			const auto& native = fileName.native();
			if (std::regex_match(native, _regex)) {
				ReadFile(dir.path());
			}
		}
	}

	void LocalePackage::ReadFile(const fs::path& a_path)
	{
		std::wifstream file(a_path, std::ios::binary);
		file.imbue(
			std::locale(file.getloc(),
				new std::codecvt_utf16<wchar_t, 0x10FFFF, CVT_MODE>));	// UCS-2 LE w/ BOM

		if (!file.is_open()) {
			logger::error("Failed to open file \"{}\"!\n", a_path.string());
			return;
		}

		std::wstring line;
		std::wstring key;
		std::wstring value;
		while (std::getline(file, line)) {
			if (!line.empty() && line.back() == L'\r')
				line.pop_back();  // discard carriage return

			if (line.empty() || line.front() != L'$')
				continue;

			key.clear();
			value.clear();

			auto pos = line.find_first_of(L'\t');
			if (pos != std::wstring::npos) {
				key = line.substr(0, pos);
				value = line.substr(pos + 1);
			}

			if (!key.empty() && !value.empty()) {
				auto sanitizedKey = Locale::SanitizeKey(key);
				if (sanitizedKey)
					key = std::move(*sanitizedKey);

				_items.insert({ std::move(key), std::move(value) });
			}
		}
	}
}
