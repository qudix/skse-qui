cmake_minimum_required(VERSION 3.24)

option(COPY_BSA "Copies any generated BSA to the MO2 directory (if specified)." OFF)
option(COPY_PEX "Copies any generated scripts to the MO2 directory (if specified). Applies after the BSA (if enabled)." ON)
option(COPY_PSC "Copies any script sources to the MO2 directory (if specified). Applies after the BSA (if enabled)." ON)

# -------- Project ----------
project(
	qui
	VERSION 0.4.1
	LANGUAGES CXX
)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

get_filename_component(
	Skyrim64Path
	"[HKEY_LOCAL_MACHINE\\SOFTWARE\\WOW6432Node\\Bethesda Softworks\\Skyrim Special Edition;installed path]"
	ABSOLUTE CACHE
)

list(APPEND CMAKE_IGNORE_PATH "${PROJECT_BINARY_DIR}")
list(APPEND CMAKE_MODULE_PATH
	"${PROJECT_SOURCE_DIR}/tools/SKSE-CMakeModules/Modules"
)
list(APPEND CMAKE_MODULE_PATH
	"${PROJECT_SOURCE_DIR}/tools/Bethesda-CMakeModules/Modules"
)

include(SKSEPlugin)
set(SKSE_USE_XBYAK ON)
find_path(CLIB_UTIL_INCLUDE_DIRS "ClibUtil/utils.hpp")

add_compile_definitions(SKSE_SUPPORT_XBYAK)
add_compile_definitions(SKYRIM_AE)
add_compile_definitions(SKYRIM_SUPPORT_AE)

set(SKSE_COMMONLIBSSE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/External/CommonLibSSE")
set(SKSE_NO_INSTALL ON)

if (GOG)
	add_compile_definitions(SKYRIM_GOG)
	set(SKSE_COMMONLIBSSE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/External/CommonLibSSE_1.6")
endif()

SKSEPlugin_Add(
	${PROJECT_NAME}
	SOURCE_DIR src
	INCLUDE_DIR include
	SOURCES
		README.md
		vcpkg.json
	PRECOMPILE_HEADERS
		src/PCH.hpp
)

set_target_properties(CommonLibSSE PROPERTIES
	FOLDER External
)

if (MSVC)
	target_compile_options(
		${PROJECT_NAME}
		PRIVATE
			/sdl                    # Enable Additional Security Checks
			/utf-8                  # Set Source and Executable character sets to UTF-8
			/Zi                     # Debug Information Format

			/permissive-            # Standards conformance
			/Zc:preprocessor        # Enable preprocessor conformance mode
			/Zc:__cplusplus
			
			/wd4200                 # nonstandard extension used : zero-sized array in struct/union
			/W4                     # More warnings 
			/WX                     # Treat all warnings as errors
			/external:anglebrackets # Ignore warnings for external resources.
			/external:W0            # Same as above
			
			"$<$<CONFIG:DEBUG>:>"
			"$<$<CONFIG:RELEASE>:/Zc:inline;/JMC-;/Ob3>"
	)

	target_link_options(
		${PROJECT_NAME}
		PRIVATE
			"$<$<CONFIG:DEBUG>:/INCREMENTAL;/OPT:NOREF;/OPT:NOICF>"
			"$<$<CONFIG:RELEASE>:/INCREMENTAL:NO;/OPT:REF;/OPT:ICF;/DEBUG:FULL>"
	)
endif ()

set(DATA_DIR "${PROJECT_SOURCE_DIR}/data")

include(components.cmake)

# ---- Post build ----
if(DEFINED ENV{SKYRIM_MODS_FOLDER} AND IS_DIRECTORY "$ENV{SKYRIM_MODS_FOLDER}")
	if(GOG)
		set(OUTPUT_FOLDER "$ENV{SKYRIM_MODS_FOLDER}/${PROJECT_NAME} - GOG")
	elseif (FULL_RELEASE)
		set(OUTPUT_FOLDER "$ENV{SKYRIM_MODS_FOLDER}/${PROJECT_NAME} - Full Release")
	else()
		set(OUTPUT_FOLDER "$ENV{SKYRIM_MODS_FOLDER}/${PROJECT_NAME} - Test")
	endif()
endif()

# ---- Automatically copy artifacts to MO2 ----
if(DEFINED OUTPUT_FOLDER AND NOT SKIP_ARTIFACTS)
    set(DLL_FOLDER "${OUTPUT_FOLDER}/SKSE/Plugins")

    add_custom_command(
        TARGET "${PROJECT_NAME}"
        POST_BUILD
        COMMAND "${CMAKE_COMMAND}" -E copy_if_different "$<TARGET_FILE:${PROJECT_NAME}>" "${DLL_FOLDER}/$<TARGET_FILE_NAME:${PROJECT_NAME}>"
        COMMAND "${CMAKE_COMMAND}" -E copy_if_different "$<TARGET_PDB_FILE:${PROJECT_NAME}>" "${DLL_FOLDER}/$<TARGET_PDB_FILE_NAME:${PROJECT_NAME}>"

		COMMAND "${CMAKE_COMMAND}"
			-DSRC_DIR="${PROJECT_SOURCE_DIR}/Data"
			-DDST_DIR="${OUTPUT_FOLDER}"
			-DPROJECT_NAME="${PROJECT_NAME}"
			-P "${PROJECT_SOURCE_DIR}/CMake/Scripts/CMake-Copy-Artifacts.cmake"
    )
endif()

# ---- Github Release Stuff ----
install(
	FILES
		"$<TARGET_FILE:${PROJECT_NAME}>"
		"$<TARGET_PDB_FILE:${PROJECT_NAME}>"
	DESTINATION "SKSE/Plugins"
	COMPONENT components
)