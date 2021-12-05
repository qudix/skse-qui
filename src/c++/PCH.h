#pragma once

#pragma warning(push)
#pragma warning(disable: 4200)
#include "SKSE/SKSE.h"
#include "RE/Skyrim.h"
#pragma warning(pop)

#include <frozen/map.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <toml++/toml.h>

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
#include "Settings.h"
