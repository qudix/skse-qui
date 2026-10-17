# ---- Validate required variables ----
foreach(var SRC_DIR DST_DIR PROJECT_NAME)
    if(NOT DEFINED ${var})
        message(FATAL_ERROR "Required variable ${var} was not provided to CopyArtifacts.cmake")
    endif()
endforeach()

# ---- Normalize paths ----
file(TO_CMAKE_PATH "${SRC_DIR}" SRC_DIR)
file(TO_CMAKE_PATH "${DST_DIR}" DST_DIR)

# ---- Plugin files (esp/esl/esm) ----
foreach(ext esp esl esm)
    set(PLUGIN_SRC "${SRC_DIR}/${PROJECT_NAME}.${ext}")
    if(EXISTS "${PLUGIN_SRC}")
        message(STATUS "Copying ${PLUGIN_SRC} to ${DST_DIR}")
        file(INSTALL
            DESTINATION "${DST_DIR}"
            TYPE FILE
            FILES "${PLUGIN_SRC}"
        )
    endif()
endforeach()

# ---- SKSE plugin config directory ----
set(PLUGIN_CONFIG_SRC "${SRC_DIR}/SKSE/Plugins/${PROJECT_NAME}")
set(PLUGIN_CONFIG_DST "${DST_DIR}/SKSE/Plugins/${PROJECT_NAME}")

file(TO_CMAKE_PATH "${PLUGIN_CONFIG_SRC}" PLUGIN_CONFIG_SRC)
file(TO_CMAKE_PATH "${PLUGIN_CONFIG_DST}" PLUGIN_CONFIG_DST)

if(EXISTS "${PLUGIN_CONFIG_SRC}" AND IS_DIRECTORY "${PLUGIN_CONFIG_SRC}")
    message(STATUS "Refreshing config directory: ${PLUGIN_CONFIG_DST}")
    if(EXISTS "${PLUGIN_CONFIG_DST}")
        file(REMOVE_RECURSE "${PLUGIN_CONFIG_DST}")
    endif()

    # Copy all contents of the source folder to the destination
    file(GLOB PLUGIN_FILES "${PLUGIN_CONFIG_SRC}/*")
    if(PLUGIN_FILES)
        foreach(f ${PLUGIN_FILES})
            get_filename_component(fname "${f}" NAME)
            file(COPY "${f}" DESTINATION "${PLUGIN_CONFIG_DST}/")
        endforeach()
        message(STATUS "Copied ${PLUGIN_CONFIG_SRC} contents to ${PLUGIN_CONFIG_DST}")
    else()
        message(STATUS "No files to copy in ${PLUGIN_CONFIG_SRC}")
    endif()
endif()

# ---- Custom Console directory ----
set(CONSOLE_CONFIG_SRC "${SRC_DIR}/SKSE/CustomConsole")
set(CONSOLE_CONFIG_DST "${DST_DIR}/SKSE/CustomConsole")
file(TO_CMAKE_PATH "${CONSOLE_CONFIG_SRC}" CONSOLE_CONFIG_SRC)
file(TO_CMAKE_PATH "${CONSOLE_CONFIG_DST}" CONSOLE_CONFIG_DST)

if(EXISTS "${CONSOLE_CONFIG_SRC}" AND IS_DIRECTORY "${CONSOLE_CONFIG_SRC}")
    if(EXISTS "${CONSOLE_CONFIG_DST}")
        file(REMOVE_RECURSE "${CONSOLE_CONFIG_DST}")
    endif()

    file(GLOB CONSOLE_FILES "${CONSOLE_CONFIG_SRC}/*")
    foreach(f ${CONSOLE_FILES})
        get_filename_component(fname "${f}" NAME)
        file(COPY "${f}" DESTINATION "${CONSOLE_CONFIG_DST}/")
    endforeach()
endif()

# ---- INI ----
set(INI_SRC "${SRC_DIR}/SKSE/Plugins/${PROJECT_NAME}.ini")
set(INI_DST "${DST_DIR}/SKSE/Plugins")
file(TO_CMAKE_PATH "${INI_SRC}" INI_SRC)
file(TO_CMAKE_PATH "${INI_DST}" INI_DST)

if(EXISTS "${INI_SRC}")
    file(MAKE_DIRECTORY "${INI_DST}")
    message(STATUS "Copying ${INI_SRC} to ${INI_DST}")
    file(INSTALL
        DESTINATION "${INI_DST}"
        TYPE FILE
        FILES "${INI_SRC}"
    )
endif()
