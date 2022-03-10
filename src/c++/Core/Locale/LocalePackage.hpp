#pragma once

namespace Core
{
	class LocalePackage final
	{
		using Items = std::unordered_map<std::wstring, std::wstring>;

	public:
		LocalePackage() = default;

		void Load();
		void Load(const std::wstring& a_lang);

		std::optional<std::wstring> FindItem(const std::wstring& a_key);

		void Dump();

	public:
		bool empty() const noexcept { return _items.empty(); }

	private:
		void LoadFiles();
		void ReadFile(const fs::path& a_path);

	private:
		std::wstring _language{ L"ENGLISH" };
		std::wregex  _regex;
		Items		 _items;
	};
}
