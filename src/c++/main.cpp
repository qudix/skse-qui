#include "Core/Core.hpp"

void InitLogger()
{
	auto path = logger::log_directory();
	if (!path)
		return;

	const auto plugin = SKSE::PluginDeclaration::GetSingleton();
	*path /= fmt::format(FMT_STRING("{}.log"), plugin->GetName());

	std::shared_ptr<spdlog::sinks::sink> sink;
	if (WinAPI::IsDebuggerPresent()) {
		sink = std::make_shared<spdlog::sinks::msvc_sink_mt>();
	} else {
		sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(path->string(), true);
	}

	auto log = std::make_shared<spdlog::logger>("global log"s, sink);
	log->set_level(spdlog::level::info);
	log->flush_on(spdlog::level::info);

	spdlog::set_default_logger(std::move(log));
	spdlog::set_pattern("%s(%#): [%^%l%$] %v"s);
}

SKSEPluginLoad(const SKSE::LoadInterface* a_skse)
{
	InitLogger();

	const auto plugin = SKSE::PluginDeclaration::GetSingleton();
	logger::info("{} v{}"sv, plugin->GetName(), plugin->GetVersion());

	SKSE::Init(a_skse);
	Core::Init();

	logger::info("{} loaded"sv, plugin->GetName());

	return true;
}
