#pragma once

#include "General/Singleton.hpp"

namespace Core::Private
{
	struct ConfigImpl
	{
		struct
		{
			std::string Locale{ "" };
		} General;

		struct
		{
			bool Enable{ true };
			bool Pause{ false };
			bool Loop{ true };
			bool Sound{ true };
			bool AutoSearch{ false };

			struct
			{
				uint32_t KeyboardToggle{ 87u };
			} Key;

			struct
			{
				uint32_t Alchemy{ 25u };
				uint32_t Ammo{ 500u };
				uint32_t Armor{ 1u };
				uint32_t Book{ 1u };
				uint32_t Ingredient{ 100u };
				uint32_t Key{ 1u };
				uint32_t Misc{ 25u };
				uint32_t Note{ 5u };
				uint32_t Scroll{ 1u };
				uint32_t Soul{ 25u };
				uint32_t Spell{ 1u };
				uint32_t Weapon{ 1u };
			} Count;

			struct
			{
				std::unordered_map<std::string, bool> Enable{};
			} Plugin;
		} PluginExplorer;

		struct
		{
			bool Enable{ true };

			struct
			{
				bool Logo{ true };
				bool Motd{ true };
				bool Banner{ true };
			} UI;

			struct
			{
				bool CC{ true };
				bool DLC{ false };
				bool Mods{ true };
				bool Credits{ true };
				bool Help{ true };
			} List;
		} MainMenu;

		struct
		{
			bool Enable{ true };
			uint32_t DefaultPage{ 2u };
		} JournalMenu;
	};
}

namespace Core
{
	class Config final :
		public ISingleton<Config>
	{
	public:
		Config() = default;

		void Load();
		void Read();

		auto GetNode(const char* a_path)
			-> toml::node_view<toml::node>;

		void GetValue(const char* a_path, bool& a_value);
		void GetValue(const char* a_path, uint32_t& a_value);
		void GetValue(const char* a_path, float& a_value);
		void GetValue(const char* a_path, std::string& a_value);
		void GetValue(const char* a_path, std::unordered_map<std::string, bool>& a_value);

		static Private::ConfigImpl& Get();

	public:
		toml::parse_result _result;
		toml::parse_result _resultCustom;

		Private::ConfigImpl _impl;
	};
}
