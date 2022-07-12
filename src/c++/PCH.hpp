#pragma once

#define _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS
#define SPDLOG_WCHAR_TO_UTF8_SUPPORT

#pragma warning(push)
#pragma warning(disable : 4200)
#include "SKSE/SKSE.h"
#include "RE/Skyrim.h"
#pragma warning(pop)

#define TOML_EXCEPTIONS 0

#include <frozen/map.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/msvc_sink.h>
#include <toml++/toml.h>

#include <source_location>

namespace WinAPI = SKSE::WinAPI;
namespace logger = SKSE::log;
namespace fs = std::filesystem;
using namespace std::literals;

namespace stl
{
	using namespace SKSE::stl;
	constexpr std::string_view safe_string(const char* a_str) { return a_str ? a_str : ""sv; }
}

#define DLLEXPORT __declspec(dllexport)

#include "Plugin.h"
