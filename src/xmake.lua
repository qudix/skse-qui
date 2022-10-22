target("QUI")
    add_packages("frozen", "toml++", "fmt", "spdlog", "commonlibsse-ng")

    add_rules("@commonlibsse-ng/plugin", {
        name = "QUI",
        author = "Qudix",
        description = "Various UI tools, tweaks, and fixes"
    })

    add_files("c++/**.cpp")
    add_includedirs("c++")
    set_pcxxheader("c++/PCH.hpp")

    add_rules("mod.package", {
        ["@{target}-@{target_ver}.zip"] = {
            { "@{target_dir}", "@{target}.dll", "Data/SKSE/Plugins/" },
            { "@{project_dir}/res/plugins/", "@{target}.toml", "Data/SKSE/Plugins/" },
            { "@{project_dir}/res/translations/", "@{target}_*.txt", "Data/Interface/Translations/" },
            { "@{project_dir}/src/swf/", "*.swf", "Data/Interface/" }
        },
        ["@{target}-@{target_ver}_pdb.zip"] = {
            { "@{target_dir}", "@{target}.pdb" },
        }
    })
