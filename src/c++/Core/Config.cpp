#include "Core/Config.hpp"

namespace Core
{
	void Config::Load()
	{
		auto plugin = SKSE::PluginDeclaration::GetSingleton();
		auto path = fmt::format("Data/SKSE/Plugins/{}.toml", plugin->GetName());
		auto pathCustom = fmt::format("Data/SKSE/Plugins/{}_Custom.toml", plugin->GetName());

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
		_impl = {};

		#define GET_VALUE(VALUE_PATH) \
			GetValue(#VALUE_PATH, _impl.VALUE_PATH);

		GET_VALUE(General.Locale);
		GET_VALUE(PluginExplorer.Enable);
		GET_VALUE(PluginExplorer.Pause);
		GET_VALUE(PluginExplorer.Loop);
		GET_VALUE(PluginExplorer.Sound);
		GET_VALUE(PluginExplorer.Key.KeyboardToggle);
		GET_VALUE(PluginExplorer.Count.Alchemy);
		GET_VALUE(PluginExplorer.Count.Ammo);
		GET_VALUE(PluginExplorer.Count.Armor);
		GET_VALUE(PluginExplorer.Count.Book);
		GET_VALUE(PluginExplorer.Count.Ingredient);
		GET_VALUE(PluginExplorer.Count.Key);
		GET_VALUE(PluginExplorer.Count.Misc);
		GET_VALUE(PluginExplorer.Count.Note);
		GET_VALUE(PluginExplorer.Count.Scroll);
		GET_VALUE(PluginExplorer.Count.Soul);
		GET_VALUE(PluginExplorer.Count.Spell);
		GET_VALUE(PluginExplorer.Count.Weapon);
		GET_VALUE(PluginExplorer.Plugin.Enable);
		GET_VALUE(MainMenu.Enable);
		GET_VALUE(MainMenu.UI.Logo);
		GET_VALUE(MainMenu.UI.Motd);
		GET_VALUE(MainMenu.UI.Banner);
		GET_VALUE(MainMenu.List.CC);
		GET_VALUE(MainMenu.List.DLC);
		GET_VALUE(MainMenu.List.Mods);
		GET_VALUE(MainMenu.List.Credits);
		GET_VALUE(MainMenu.List.Help);
		GET_VALUE(JournalMenu.Enable);
		GET_VALUE(JournalMenu.DefaultPage);

		#undef GET_VALUE
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

	void Config::GetValue(const char* a_path, bool& a_value)
	{
		auto node = GetNode(a_path);
		if (node && node.is_boolean())
			a_value = node.value_or(a_value);
	}

	void Config::GetValue(const char* a_path, uint32_t& a_value)
	{
		auto node = GetNode(a_path);
		if (node && node.is_integer())
			a_value = node.value_or(a_value);
	}

	void Config::GetValue(const char* a_path, float& a_value)
	{
		auto node = GetNode(a_path);
		if (node && node.is_floating_point())
			a_value = node.value_or(a_value);
	}

	void Config::GetValue(const char* a_path, std::string& a_value)
	{
		auto node = GetNode(a_path);
		if (node && node.is_string())
			a_value = node.value_or(a_value);
	}

	void Config::GetValue(const char* a_path, std::unordered_map<std::string, bool>& a_value)
	{
		auto node = GetNode(a_path);
		if (node) {
			if (node.is_table()) {
				for (const auto& [key, value] : *node.as_table()) {
					auto opt = value.value<bool>();
					if (opt && !key.empty())
						a_value[key.data()] = opt.value();
				}
			}
		}
	}

	Private::ConfigImpl& Config::Get()
	{
		auto config = GetSingleton();
		return config->_impl;
	}
}
