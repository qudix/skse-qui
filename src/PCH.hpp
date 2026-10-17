#pragma once

#define _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS
#define TOML_EXCEPTIONS 0
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#define DLLEXPORT __declspec(dllexport)

#pragma warning(push)
#pragma warning(disable : 4200)
#include <SKSE/SKSE.h>
#include <RE/Skyrim.h>
#pragma warning(pop)

#include <frozen/map.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/msvc_sink.h>
#include <toml++/toml.h>

#include <source_location>

#include "Plugin.h"

namespace WinAPI = REX::W32;
// 0.4.1 -> Commonlib switched to REX
//namespace logger = SKSE::log;
namespace fs = std::filesystem;
using namespace std::literals;
