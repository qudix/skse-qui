foreach(var SRC_DIR DST_DIR PROJECT_NAME BINARY_DIR)
    if(NOT DEFINED ${var})
        message(FATAL_ERROR "Required variable ${var} was not provided to CopyArchive.cmake")
    endif()
endforeach()

set(BSA_SRC "${BINARY_DIR}/${PROJECT_NAME}.bsa")

if(EXISTS "${BSA_SRC}")
    message(STATUS "Copying ${BSA_SRC} to ${DST_DIR}")
    file(INSTALL
        DESTINATION "${DST_DIR}"
        TYPE FILE
        FILES "${BSA_SRC}"
    )
else()
    message(STATUS "BSA file not found: ${BSA_SRC}")
endif()
