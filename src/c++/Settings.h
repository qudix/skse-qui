#pragma once

class Settings
{
public:
	struct PluginExplorer_
	{
		bool Pause;
		bool Loop;
		bool Sound;

		struct
		{
			uint32_t KeyboardToggle;
		} Key;

		struct
		{
			uint32_t Alchemy;
			uint32_t Ammo;
			uint32_t Armor;
			uint32_t Book;
			uint32_t Key;
			uint32_t Misc;
			uint32_t Note;
			uint32_t Spell;
			uint32_t Weapon;
		} Count;
	};

	struct MainMenu_
	{
		struct
		{
			bool Logo;
			bool Motd;
		} UI;

		struct
		{
			bool CC;
			bool DLC;
			bool Mods;
			bool Credits;
			bool Help;
		} List;
	};

	static void Load()
	{
		try {
			const auto table = toml::parse_file(
				fmt::format("Data/SKSE/Plugins/{}.toml", Plugin::NAME));

			const auto pluginExplorer = table["PluginExplorer"];
			PluginExplorer = {
				.Pause = *pluginExplorer["Pause"].value<bool>(),
				.Loop = *pluginExplorer["Loop"].value<bool>(),
				.Sound = *pluginExplorer["Sound"].value<bool>()
			};

			const auto pluginExplorerKey = pluginExplorer["Key"];
			PluginExplorer.Key = {
				.KeyboardToggle = *pluginExplorerKey["KeyboardToggle"].value<uint32_t>()
			};

			const auto pluginExplorerCount = pluginExplorer["Count"];
			PluginExplorer.Count = {
				.Alchemy = *pluginExplorerCount["Alchemy"].value<uint32_t>(),
				.Ammo = *pluginExplorerCount["Ammo"].value<uint32_t>(),
				.Armor = *pluginExplorerCount["Armor"].value<uint32_t>(),
				.Book = *pluginExplorerCount["Book"].value<uint32_t>(),
				.Key = *pluginExplorerCount["Key"].value<uint32_t>(),
				.Misc = *pluginExplorerCount["Misc"].value<uint32_t>(),
				.Note = *pluginExplorerCount["Note"].value<uint32_t>(),
				.Spell = *pluginExplorerCount["Spell"].value<uint32_t>(),
				.Weapon = *pluginExplorerCount["Weapon"].value<uint32_t>()
			};

			const auto mainMenu = table["MainMenu"];
			const auto mainMenuUI = mainMenu["UI"];
			MainMenu.UI = {
				.Logo = *mainMenuUI["Logo"].value<bool>(),
				.Motd = *mainMenuUI["Motd"].value<bool>()
			};

			const auto mainMenuList = mainMenu["List"];
			MainMenu.List = {
				.CC = *mainMenuList["CC"].value<bool>(),
				.DLC = *mainMenuList["DLC"].value<bool>(),
				.Mods = *mainMenuList["Mods"].value<bool>(),
				.Credits = *mainMenuList["Credits"].value<bool>(),
				.Help = *mainMenuList["Help"].value<bool>()
			};

		} catch (const toml::parse_error& e) {
			std::ostringstream ss;
			ss << "Error parsing file \'" << *e.source().path << "\':\n"
			   << '\t' << e.description() << '\n'
			   << "\t\t(" << e.source().begin << ')';
			logger::error(ss.str());
			stl::report_and_fail("failed to load settings"sv);
		} catch (const std::exception& e) {
			stl::report_and_fail(e.what());
		} catch (...) {
			stl::report_and_fail("unknown failure"sv);
		}
	}

	static inline PluginExplorer_ PluginExplorer;
	static inline MainMenu_ MainMenu;
};
