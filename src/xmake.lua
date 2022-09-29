target("QUI")
    add_packages("frozen", "toml++", "fmt", "spdlog", "commonlibsse-ng")

    add_rules("commonlibsse.plugin", {
        name = "QUI",
        author = "Qudix",
        license = "GPL-3.0",
        sources = {
            files = { "src/c++/**.cpp" },
            headers = { "src/c++/**.hpp" },
            include = "src/c++",
            pch = "src/c++/PCH.hpp"
        }
    })

    add_rules("commonlibsse.plugin.package", {
        files = {
            { "@{target_dir}", "*.dll", "Data/SKSE/Plugins/" },
            { "$(projectdir)/res/plugins/", "@{plugin}.toml", "Data/SKSE/Plugins/" },
            { "$(projectdir)/res/translations/", "@{plugin}_*.txt", "Data/Interface/Translations/" },
            { "$(projectdir)/src/swf/", "*.swf", "Data/Interface/" }
        }
    })
