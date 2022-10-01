rule("commonlibsse.plugin")
    add_deps("c++", "win.sdk.resource")

    on_load(function(a_target)
        import("core.base.semver")
        import("core.project.project")

        a_target:set("kind", "shared")
        a_target:set("arch", "x64")
        a_target:add("languages", "c++20")

        local get_plugin_conf = function(a_conf)
            return a_target:extraconf("rules", "commonlibsse.plugin", a_conf)
        end

        local plugin_name = get_plugin_conf("name") or project.name()
        local plugin_author = get_plugin_conf("author") or ""
        local plugin_email = get_plugin_conf("email") or ""
        local plugin_license = get_plugin_conf("license") or ""
        local plugin_version = get_plugin_conf("version") or project.version()
        local plugin_semver = semver.new(plugin_version)
        local plugin_options = get_plugin_conf("options") or {}
        local plugin_sources = get_plugin_conf("sources")

        a_target:set("basename", plugin_name)

        local config_dir = path.join("$(buildir)", ".config", a_target:name())
        if not os.exists(config_dir) then
            os.mkdir(config_dir)
        end

        io.writefile(path.join(config_dir, "version.rc.in"),
            "#include <winres.h>\n"..
            "\n"..
            "1 VERSIONINFO\n"..
            "FILEVERSION ${PLUGIN_VERSION_MAJOR}, ${PLUGIN_VERSION_MINOR}, ${PLUGIN_VERSION_PATCH}, 0\n"..
            "PRODUCTVERSION ${PLUGIN_VERSION_MAJOR}, ${PLUGIN_VERSION_MINOR}, ${PLUGIN_VERSION_PATCH}, 0\n"..
            "FILEFLAGSMASK 0x17L\n"..
            "#ifdef _DEBUG\n"..
            "FILEFLAGS 0x1L\n"..
            "#else\n"..
            "FILEFLAGS 0x0L\n"..
            "#endif\n"..
            "FILEOS 0x4L\n"..
            "FILETYPE 0x1L\n"..
            "FILESUBTYPE 0x0L\n"..
            "BEGIN\n"..
            "BLOCK \"StringFileInfo\"\n"..
            "BEGIN\n"..
            "    BLOCK \"040904b0\"\n"..
            "    BEGIN\n"..
            "        VALUE \"FileDescription\", \"${PLUGIN_NAME}\"\n"..
            "        VALUE \"FileVersion\", \"${PLUGIN_VERSION}.0\"\n"..
            "        VALUE \"InternalName\", \"${PLUGIN_NAME}\"\n"..
            "        VALUE \"LegalCopyright\", \"${PLUGIN_LICENSE}\"\n"..
            "        VALUE \"ProductName\", \"${PLUGIN_NAME}\"\n"..
            "        VALUE \"ProductVersion\", \"${PLUGIN_VERSION}.0\"\n"..
            "    END\n"..
            "END\n"..
            "BLOCK \"VarFileInfo\"\n"..
            "BEGIN\n"..
            "    VALUE \"Translation\", 0x409, 1200\n"..
            "END\n"..
            "END\n")

        io.writefile(path.join(config_dir, "plugin.cpp.in"),
            "#include <REL/Relocation.h>\n"..
            "#include <SKSE/SKSE.h>\n"..
            "\n"..
            "SKSEPluginInfo(\n"..
            "    .Version = { ${PLUGIN_VERSION_MAJOR}, ${PLUGIN_VERSION_MINOR}, ${PLUGIN_VERSION_PATCH}, 0 },\n"..
            "    .Name = \"${PLUGIN_NAME}\"sv,\n"..
            "    .Author = \"${PLUGIN_AUTHOR}\"sv,\n"..
            "    .SupportEmail = \"${PLUGIN_EMAIL}\"sv,\n"..
            "    .StructCompatibility = ${PLUGIN_OPTION_STRUCT_COMPATIBILITY},\n"..
            "    .RuntimeCompatibility = ${PLUGIN_OPTION_RUNTIME_COMPATIBILITY}\n"..
            ")\n")

        a_target:set("configdir", config_dir)
        a_target:add("configfiles", path.join(config_dir, "*.in"))
        a_target:add("files", path.join(config_dir, "*.rc"))
        a_target:add("files", path.join(config_dir, "*.cpp"))

        a_target:set("configvar", "PLUGIN_NAME", plugin_name)
        a_target:set("configvar", "PLUGIN_AUTHOR", plugin_author)
        a_target:set("configvar", "PLUGIN_EMAIL", plugin_email)
        a_target:set("configvar", "PLUGIN_LICENSE", plugin_license)
        a_target:set("configvar", "PLUGIN_VERSION", plugin_version)
        a_target:set("configvar", "PLUGIN_VERSION_MAJOR", plugin_semver:major())
        a_target:set("configvar", "PLUGIN_VERSION_MINOR", plugin_semver:minor())
        a_target:set("configvar", "PLUGIN_VERSION_PATCH", plugin_semver:patch())

        a_target:set("configvar", "PLUGIN_OPTION_STRUCT_COMPATIBILITY", "SKSE::StructCompatibility::Independent")

        local address_library = plugin_options.address_library or true
        local signature_scanning = plugin_options.signature_scanning or false
        if (address_library or signature_scanning) then
            if (address_library) then
                a_target:set("configvar", "PLUGIN_OPTION_RUNTIME_COMPATIBILITY", "SKSE::VersionIndependence::AddressLibrary")
            else
                a_target:set("configvar", "PLUGIN_OPTION_RUNTIME_COMPATIBILITY", "SKSE::VersionIndependence::SignatureScanning")
            end
        end

        for _, files in pairs(plugin_sources.files) do
            a_target:add("files", files)
        end

        for _, headers in pairs(plugin_sources.headers) do
            a_target:add("headerfiles", headers)
        end

        a_target:add("includedirs", plugin_sources.include)

        if plugin_sources.pch then
            a_target:set("pcxxheader", plugin_sources.pch)
        end

        a_target:add("defines", "UNICODE", "_UNICODE")

        a_target:add("cxxflags", "/MP", "/permissive-")
        a_target:add("cxxflags",
            "/Zc:alignedNew",
            "/Zc:__cplusplus",
            "/Zc:externConstexpr",
            "/Zc:forScope",
            "/Zc:hiddenFriend",
            "/Zc:preprocessor",
            "/Zc:referenceBinding",
            "/Zc:ternary")
    end)

rule("commonlibsse.plugin.package")
    on_package(function(a_target)
        import("core.base.semver")
        import("core.project.project")
        import("utils.archive")

        local get_plugin_conf = function(a_conf)
            return a_target:extraconf("rules", "commonlibsse.plugin", a_conf)
        end

        local plugin_name = get_plugin_conf("name")
        local plugin_version = get_plugin_conf("version") or project.version()
        local plugin_semver = semver.new(plugin_version)

        function parse_str(a_str)
            if not a_str then
                return nil
            end

            local var_map = {
                plugin = plugin_name,
                plugin_ver = plugin_version,
                plugin_ver_major = plugin_semver:major(),
                plugin_ver_minor = plugin_semver:minor(),
                plugin_ver_patch = plugin_semver:minor(),
                target_dir = path.join(os.projectdir(), a_target:targetdir())
            }

            a_str = a_str:gsub("(%@{([^\n]-)})", function(_, a_var)
                a_var = a_var:trim()
                local value = var_map[a_var]
                assert(value ~= nil, "cannot get variable(%s)", a_var)
                return value
            end)

            return a_str
        end

        local packages_dir = path.join(os.projectdir(), "$(buildir)", "packages")
        local packages_plugin_dir = path.join(packages_dir, plugin_name)
        if not os.exists(packages_plugin_dir) then
            os.tryrm(packages_plugin_dir)
        end

        os.mkdir(packages_plugin_dir)

        local packages = a_target:extraconf("rules", "commonlibsse.plugin.package", "packages")
        for id, package in pairs(packages) do
            if package.name and package.files then
                local package_name = parse_str(package.name)
                local package_dir = path.join(packages_plugin_dir, id)
                os.mkdir(package_dir)

                for _, item in pairs(package.files) do
                    local root = parse_str(item[1])
                    local src = path.join(root, parse_str(item[2]))
                    local dest = path.join(package_dir, parse_str(item[3] or ""))

                    if not os.exists(dest) then
                        os.mkdir(dest)
                    end

                    os.trycp(src, dest, { rootdir = root })
                end

                local old_dir = os.cd(package_dir)
                archive.archive(path.join("../", package_name), ".")
                os.cd(old_dir)
            end
        end
    end)
