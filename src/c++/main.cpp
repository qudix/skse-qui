#include "Event/Event.h"
#include "Menus/Menus.h"

void OnInit(SKSE::MessagingInterface::Message* a_msg)
{
	switch (a_msg->type) {
	case SKSE::MessagingInterface::kDataLoaded:
		Event::Register();
		Menus::Register();
		break;
	}
}

bool StartLogger()
{
	auto path = logger::log_directory();
	if (!path)
		return false;

	*path /= fmt::format(FMT_STRING("{}.log"), Version::PROJECT);
	auto sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(path->string(), true);
	auto log = std::make_shared<spdlog::logger>("global log"s, std::move(sink));

	log->set_level(spdlog::level::info);
	log->flush_on(spdlog::level::info);

	spdlog::set_default_logger(std::move(log));
	spdlog::set_pattern("%s(%#): [%^%l%$] %v"s);

	logger::info("{} v{}"sv, Version::PROJECT, Version::NAME);

	return true;
}

#ifdef IS_SKYRIM_AE

extern "C" DLLEXPORT constinit auto SKSEPlugin_Version = []() {
	SKSE::PluginVersionData v{};
	v.PluginVersion({ Version::MAJOR, Version::MINOR, Version::PATCH });
	v.PluginName(Version::NAME);
	v.AuthorName("Qudix"sv);
	v.CompatibleVersions({ SKSE::RUNTIME_1_6_318 });
	return v;
}();

#else

extern "C" DLLEXPORT bool SKSEAPI SKSEPlugin_Query(const SKSE::QueryInterface* a_skse, SKSE::PluginInfo* a_info)
{
	if (!StartLogger())
		return false;

	a_info->infoVersion = SKSE::PluginInfo::kVersion;
	a_info->name = Version::PROJECT.data();
	a_info->version = Version::MAJOR;

	if (a_skse->IsEditor()) {
		logger::critical("Loaded in editor, marking as incompatible"sv);
		return false;
	}

	const auto ver = a_skse->RuntimeVersion();
	if (ver < SKSE::RUNTIME_1_5_39) {
		logger::critical("Unsupported runtime version {}"sv, ver.string());
		return false;
	}

	return true;
}

#endif

extern "C" DLLEXPORT bool SKSEAPI SKSEPlugin_Load(const SKSE::LoadInterface* a_skse)
{
	#ifdef IS_SKYRIM_AE
	if (!StartLogger())
		return false;
	#endif

	SKSE::Init(a_skse);
	Settings::Load();
	Menus::Load();

	const auto messaging = SKSE::GetMessagingInterface();
	messaging->RegisterListener("SKSE", OnInit);

	logger::info("{} loaded"sv, Version::PROJECT);

	return true;
}
