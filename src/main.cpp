#include "Core/Core.hpp"

#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/msvc_sink.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/spdlog.h>

static void SetupLog()
{
#ifndef NDEBUG
#define SPD_LOG_LEVEL spdlog::level::debug
#else
#define SPD_LOG_LEVEL spdlog::level::info
#endif

	auto path = SKSE::log::log_directory();
	if (!path)
		return;

	*path /= std::format("{}.log", Plugin::NAME);

	std::vector<spdlog::sink_ptr> sinks{
		std::make_shared<spdlog::sinks::msvc_sink_mt>()
	};
	sinks.push_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>(path->string(), true));

	auto logger = std::make_shared<spdlog::logger>("global", sinks.begin(), sinks.end());
	logger->set_level(SPD_LOG_LEVEL);
	logger->flush_on(SPD_LOG_LEVEL);

	spdlog::set_default_logger(std::move(logger));
	spdlog::set_pattern("[%T.%e] [%=5t] [%L] %v");

	REX::INFO("{} v{}", Plugin::NAME, Plugin::VERSION.string());
}

extern "C" DLLEXPORT constinit auto SKSEPlugin_Version = []() {
	SKSE::PluginVersionData v{};

	v.PluginVersion(Plugin::VERSION);
	v.PluginName(Plugin::NAME);
	v.AuthorName("SeaSparrow"sv);
	v.UsesAddressLibrary();
	v.UsesUpdatedStructs();

	return v;
}();

SKSE_PLUGIN_QUERY(const SKSE::QueryInterface* a_skse, SKSE::PluginInfo* a_info)
{
	a_info->infoVersion = SKSE::PluginInfo::kVersion;
	a_info->name = Plugin::NAME.data();
	a_info->version = Plugin::VERSION[0];

	if (a_skse->IsEditor()) {
		REX::CRITICAL("Loaded in editor, marking as incompatible"sv);
		return false;
	}

	return true;
}

SKSE_PLUGIN_LOAD(const SKSE::LoadInterface* a_skse)
{
	SetupLog();

	SKSE::Init(a_skse);
	Core::Init();

	return true;
}