cmake_minimum_required(VERSION 3.21)

set(ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}")

# ---- Options ----

option(COPY_OUTPUT "Copy the output of build operations to the game directory." OFF)
option(USE_AE "Use Anniversary Edition" OFF)

# ---- Project ----

project(
    QUI
    VERSION 0.2.5
    LANGUAGES CXX
)

configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/etc/template/Plugin.h.in"
    "${CMAKE_CURRENT_BINARY_DIR}/include/Plugin.h"
    @ONLY
)

configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/etc/template/version.rc.in"
    "${CMAKE_CURRENT_BINARY_DIR}/version.rc"
    @ONLY
)

# ---- Globals ----

set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "CMake")
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ---- Include guards ----

if("${PROJECT_SOURCE_DIR}" STREQUAL "${PROJECT_BINARY_DIR}")
    message(FATAL_ERROR "In-source builds are not allowed.")
endif()

# ---- Cache build vars ----

macro(set_from_env VARIABLE)
    if(NOT DEFINED ${VARIABLE} AND DEFINED ENV{${VARIABLE}})
        set(${VARIABLE} $ENV{${VARIABLE}})
    endif()
endmacro()

set_from_env(Skyrim64Path)

# ---- Dependencies ----

if(USE_AE)
    add_subdirectory("lib/CommonLibAE" CommonLibSSE)
else()
    add_subdirectory("lib/CommonLibSSE" CommonLibSSE)
endif()

find_package(spdlog REQUIRED CONFIG)
find_package(frozen REQUIRED CONFIG)
find_package(tomlplusplus REQUIRED CONFIG)

# ---- Add source files ----

include(etc/cmake/source-list.cmake)

source_group(
    TREE "${CMAKE_CURRENT_SOURCE_DIR}"
    FILES ${CXX_FILES}
)

source_group(
    TREE "${CMAKE_CURRENT_BINARY_DIR}"
    FILES "${CMAKE_CURRENT_BINARY_DIR}/include/Plugin.h"
)

# ---- Create DLL ----

add_library(
    "${PROJECT_NAME}"
    SHARED
        ${CXX_FILES}
        "${CMAKE_CURRENT_BINARY_DIR}/include/Plugin.h"
        "${CMAKE_CURRENT_BINARY_DIR}/version.rc"
        "res/QUI.toml"
        ".clang-format"
        ".editorconfig"
)

target_compile_features(
    "${PROJECT_NAME}"
    PRIVATE
        cxx_std_20
)

if (USE_AE)
    add_compile_definitions(IS_SKYRIM_AE)
endif()

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    target_compile_options(
        "${PROJECT_NAME}"
        PRIVATE
            "/sdl"   # Enable Additional Security Checks
            "/utf-8" # Set Source and Executable character sets to UTF-8
            "/Zi"    # Debug Information Format

            "/permissive-"     # Standards conformance
            "/Zc:preprocessor" # Enable preprocessor conformance mode

            "/wd4201" # nonstandard extension used : nameless struct/union

            "$<$<CONFIG:DEBUG>:>"
            "$<$<CONFIG:RELEASE>:/Zc:inline;/JMC-;/Ob3>"
    )

    target_link_options(
        "${PROJECT_NAME}"
        PRIVATE
            "$<$<CONFIG:DEBUG>:/INCREMENTAL;/OPT:NOREF;/OPT:NOICF>"
            "$<$<CONFIG:RELEASE>:/INCREMENTAL:NO;/OPT:REF;/OPT:ICF;/DEBUG:FULL>"
    )
endif()

target_include_directories(
    "${PROJECT_NAME}"
    PRIVATE
        "${CMAKE_CURRENT_BINARY_DIR}/include"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/c++"
)

target_link_libraries(
    "${PROJECT_NAME}"
    PUBLIC
        CommonLibSSE::CommonLibSSE
        spdlog::spdlog
        frozen::frozen
        tomlplusplus::tomlplusplus
)

target_precompile_headers(
    "${PROJECT_NAME}"
    PRIVATE
        "src/c++/PCH.hpp"
)

# ---- File copying ----

if("${COPY_OUTPUT}")
    if(DEFINED Skyrim64Path)
        add_custom_command(
            TARGET "${PROJECT_NAME}"
            POST_BUILD
                COMMAND "${CMAKE_COMMAND}" -E make_directory "${Skyrim64Path}/Data/SKSE/Plugins/"
                COMMAND "${CMAKE_COMMAND}" -E copy_if_different "$<TARGET_FILE:${PROJECT_NAME}>" "${Skyrim64Path}/Data/SKSE/Plugins/"
                COMMAND "${CMAKE_COMMAND}" -E copy_if_different "${CMAKE_SOURCE_DIR}/res/QUI.toml" "${Skyrim64Path}/Data/SKSE/Plugins/"
                COMMAND "${CMAKE_COMMAND}" -E make_directory "${Skyrim64Path}/Data/Interface/"
                COMMAND "${CMAKE_COMMAND}" -E copy_if_different "${CMAKE_SOURCE_DIR}/src/swf/PluginExplorerMenu.swf" "${Skyrim64Path}/Data/Interface/"
                COMMAND "${CMAKE_COMMAND}" -E copy_if_different "${CMAKE_SOURCE_DIR}/src/swf/StartMenuEx.swf" "${Skyrim64Path}/Data/Interface/"
            VERBATIM
        )
    else()
        message(WARNING "Variable Skyrim64Path is not defined. Skipping post-build copy command.")
    endif()
endif()

include(etc/cmake/archive-artifacts.cmake)
