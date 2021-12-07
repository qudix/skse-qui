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

#ifndef IS_SKYRIM_AE
	constexpr std::uint32_t version_pack(REL::Version a_version) noexcept
	{
		return static_cast<std::uint32_t>(
			(a_version[0] & 0x0FF) << 24u |
			(a_version[1] & 0x0FF) << 16u |
			(a_version[2] & 0xFFF) << 4u |
			(a_version[3] & 0x00F) << 0u);
	}
#endif
}

#define DLLEXPORT __declspec(dllexport)

#include "Plugin.h"
#include "Settings.h"
