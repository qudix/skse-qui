#pragma once

#define MAKE_SETTING(a_type, a_group, a_key, a_value) \
	inline a_type a_key { a_group##s, #a_key##s, a_value }

namespace Settings
{
	using ISetting = AutoTOML::ISetting;
	using bSetting = AutoTOML::bSetting;
	using iSetting = AutoTOML::iSetting;

	inline void Load()
	{
		try {
			const auto table = toml::parse_file(
				fmt::format("Data/SKSE/Plugins/{}.toml", Version::PROJECT));
			for (const auto& setting : ISetting::get_settings()) {
				setting->load(table);
			}
		} catch (const toml::parse_error& e) {
			std::ostringstream ss;
			ss  << "Error parsing file \'" << *e.source().path << "\':\n"
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

	MAKE_SETTING(iSetting, "Key", PluginExplorerKey, 87); // F11
}

#undef MAKE_SETTING
