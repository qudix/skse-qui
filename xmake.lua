includes("lib/commonlibsse")

set_project("skse-qui")
set_version("0.3.2")
set_license("GPL-3.0")
set_languages("c++23")
set_warnings("allextra")

add_rules("mode.debug", "mode.releasedbg")
add_rules("plugin.vsxmake.autoupdate")

add_requires("frozen 1.2.0", "imgui", "toml++")

target("skse-qui")
    add_packages("frozen", "imgui", "toml++")

    add_rules("commonlibsse.plugin", {
        name = "skse-qui",
        author = "qudix",
        description = "Various UI tools, tweaks, and fixes"
    })

    add_files("src/c++/**.cpp")
    add_headerfiles("src/c++/**.h")
    add_includedirs("src/c++")
    set_pcxxheader("src/c++/pch.h")

    add_installfiles("res/(**)")
