#include "Core/Config.hpp"

namespace Core
{
	void Config::Load()
	{
		auto path = fmt::format("Data/SKSE/Plugins/{}.toml", Plugin::NAME);
		auto pathCustom = fmt::format("Data/SKSE/Plugins/{}_Custom.toml", Plugin::NAME);

		_result = toml::parse_file(path);
		if (!_result) {
			logger::info("Default file failed!");
			std::ostringstream ss;
			ss << "Failed to load config:\n"
			   << "Error parsing file:\n"
			   << _result.error() << "\n";
			logger::error("{}", ss.str());
			stl::report_and_fail(ss.str());
		}

		_resultCustom = toml::parse_file(pathCustom);
		bool exists = fs::exists(pathCustom);
		if (!_resultCustom && exists) {
			std::ostringstream ss;
			ss << "Failed to load custom config:\n"
			   << "Error parsing file:\n"
			   << _resultCustom.error() << "\n";
			logger::error("{}", ss.str());
			stl::report_and_fail(ss.str());
		}
	}

	void Config::Read()
	{
		_impl = {
			.PluginExplorer = {
				.Pause = GetValue("PluginExplorer.Pause", false),
				.Loop = GetValue("PluginExplorer.Loop", true),
				.Sound = GetValue("PluginExplorer.Sound", true),
				.Key = {
					.KeyboardToggle = GetValue("PluginExplorer.Key.KeyboardToggle", 87u),
				},
				.Count = {
					.Alchemy = GetValue("PluginExplorer.Count.Alchemy", 25u),
					.Ammo = GetValue("PluginExplorer.Count.Ammo", 500u),
					.Armor = GetValue("PluginExplorer.Count.Armor", 1u),
					.Book = GetValue("PluginExplorer.Count.Book", 1u),
					.Ingredient = GetValue("PluginExplorer.Count.Ingredient", 100u),
					.Key = GetValue("PluginExplorer.Count.Key", 1u),
					.Misc = GetValue("PluginExplorer.Count.Misc", 25u),
					.Note = GetValue("PluginExplorer.Count.Note", 5u),
					.Scroll = GetValue("PluginExplorer.Count.Scroll", 1u),
					.Soul = GetValue("PluginExplorer.Count.Soul", 25u),
					.Spell = GetValue("PluginExplorer.Count.Spell", 1u),
					.Weapon = GetValue("PluginExplorer.Count.Weapon", 1u),
				} },
				.MainMenu = {
					.UI = {
						.Logo = GetValue("MainMenu.UI.Logo", true),
						.Motd = GetValue("MainMenu.UI.Motd", true),
					},
				.List = {
					.CC = GetValue("MainMenu.List.CC", true),
					.DLC = GetValue("MainMenu.List.DLC", false),
					.Mods = GetValue("MainMenu.List.Mods", true),
					.Credits = GetValue("MainMenu.List.Credits", true),
					.Help = GetValue("MainMenu.List.Help", true),
				} }
		};
	}

	auto Config::GetNode(const char* a_path) -> toml::node_view<toml::node>
	{
		if (_resultCustom) {
			auto& table = _resultCustom.table();
			auto node = table.at_path(a_path);
			if (node)
				return node;
		}

		if (_result) {
			auto& table = _result.table();
			auto node = table.at_path(a_path);
			if (node)
				return node;
		}

		return {};
	}

	bool Config::GetValue(const char* a_path, bool a_default)
	{
		auto node = GetNode(a_path);
		return node.value_or(a_default);
	}

	uint32_t Config::GetValue(const char* a_path, uint32_t a_default)
	{
		auto node = GetNode(a_path);
		return node.value_or(a_default);
	}

	Private::ConfigImpl& Config::Get()
	{
		auto config = GetSingleton();
		return config->_impl;
	}
}
