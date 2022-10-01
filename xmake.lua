set_xmakever("2.7.1")

-- project
set_project("QUI")
set_version("0.3.1")
set_languages("c++20")
set_optimize("faster")
set_warnings("allextra", "error")

-- allowed
set_allowedarchs("x64")
set_allowedmodes("debug", "releasedbg")

-- default
set_defaultarchs("x64")
set_defaultmode("releasedbg")

-- rules
add_rules("mode.debug", "mode.releasedbg")

-- policies
set_policy("build.optimization.lto", true)
set_policy("package.requires_lock", true)

-- packages
add_requires("fmt", "spdlog", "frozen", "toml++")
add_requires("commonlibsse-ng", { configs = { skyrim_vr = false }})

includes("res/commonlib.lua")
includes("src")
