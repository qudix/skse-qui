#pragma once

#include "General/Singleton.hpp"

namespace Core
{
	class LocaleManager final :
		public General::Singleton<LocaleManager>
	{
	public:
		LocaleManager();

		std::wstring GetLocalization(const std::wstring& a_key);
		std::string GetLocalization(const std::string& a_key);

		std::string Translate(const std::string& a_key);
		void SetOverride(const std::string& a_locale = "");

		void Dump();

	private:
		using LocalizationMap = std::unordered_map<std::wstring, std::wstring>;
		using size_type = std::wstring::size_type;

		bool FindFiles(
			const std::filesystem::path& a_path,
			const std::wregex& a_pattern,
			bool a_english);

		void ReadFromFile(
			const std::filesystem::path& a_path,
			bool a_english);

		bool LoadLocalizationStrings(bool a_override = false);

		LocalizationMap& GetLocalizationMap();
		std::wstring GetLocalizationInternal(const std::wstring& a_key);

		std::optional<std::wstring> SanitizeKey(std::wstring a_key);

		std::optional<std::wstring> FindLocalization(const std::wstring& a_key);

		bool GetNestedLocalizations(
			const std::wstring& a_key,
			std::stack<size_type>& a_stack,
			std::queue<std::wstring>& a_queue);

		bool InsertLocalizations(
			std::wstring& a_localization,
			std::stack<size_type>& a_stack,
			std::queue<std::wstring>& a_queue);

		LocalizationMap _localizations_ENG;
		LocalizationMap _localizations_LOC;
		std::wstring _localeOverride{ L"" };
	};
}
