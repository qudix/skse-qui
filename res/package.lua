rule("mod.package")
    on_package(function(a_target)
        import("core.base.semver")
        import("core.project.project")
        import("utils.archive")

        local function _parse_str(a_target, a_str)
            assert(a_target)
            assert(a_str)

            local map = {
                project =           function() return project.name() or "" end,
                project_ver =       function() return project.version() or "0.0.0" end,
                project_ver_major = function() return semver.new(map.project_ver()):major() end,
                project_ver_minor = function() return semver.new(map.project_ver()):minor() end,
                project_ver_patch = function() return semver.new(map.project_ver()):patch() end,
                project_dir =       function() return os.projectdir() end,
                target =            function() return a_target:name() or "" end,
                target_ver =        function() return a_target:version() or "0.0.0" end,
                target_ver_major =  function() return semver.new(map.target_ver()):major() end,
                target_ver_minor =  function() return semver.new(map.target_ver()):minor() end,
                target_ver_patch =  function() return semver.new(map.target_ver()):patch() end,
                target_dir =        function() return path.join(os.projectdir(), a_target:targetdir()) end,
            }

            a_str = a_str:gsub("(%@{([^\n]-)})", function(_, a_var)
                a_var = a_var:trim()

                local result = map[a_var]
                if type(result) == "function" then
                    result = result()
                end

                assert(result ~= nil, "cannot get variable(%s)", a_var)
                return result
            end)

            return a_str
        end

        local packages_dir = path.join(os.projectdir(), "$(buildir)", "packages")
        os.mkdir(packages_dir)

        local packages = a_target:extraconf("rules", "mod.package") or {}
        for name, files in pairs(packages) do
            if name and files then
                local package_name = _parse_str(a_target, name)
                local package_dir = path.join(packages_dir, package_name:match("(.+)%..+$"))
                os.mkdir(package_dir)

                for _, file in pairs(files) do
                    local root = _parse_str(a_target, file[1])
                    local src = path.join(root, _parse_str(a_target, file[2]))
                    local dest = path.join(package_dir, _parse_str(a_target, file[3] or ""))

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

    after_clean(function()
        local packages_dir = path.join(os.projectdir(), "$(buildir)", "packages")
        os.tryrm(packages_dir)
    end)
