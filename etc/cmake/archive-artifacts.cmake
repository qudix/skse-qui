find_package(
	Python3
	MODULE
	REQUIRED
	COMPONENTS
		Interpreter
)

set(SCRIPT "${ROOT_DIR}/etc/scripts/archive-artifacts.py")

if("${SKYRIM_SUPPORT_AE}")
	set(ARCHIVE_NAME "${PROJECT_NAME}-AE-${PROJECT_VERSION}")
else()
	set(ARCHIVE_NAME "${PROJECT_NAME}-SE-${PROJECT_VERSION}")
endif()

source_group(
	TREE "${ROOT_DIR}"
	FILES "${SCRIPT}"
)

add_custom_target(
	"ArchiveArtifacts"
	COMMAND
		"$<TARGET_FILE:Python3::Interpreter>"
		"${SCRIPT}"
        "--name=${ARCHIVE_NAME}"
		"--bin-dir=${ROOT_DIR}"
		"--plugin-files"
			"$<TARGET_FILE:${PROJECT_NAME}>"
			"${ROOT_DIR}/res/${PROJECT_NAME}.toml"
		"--pdb-files=$<TARGET_PDB_FILE:${PROJECT_NAME}>"
		"--swf-files"
            "${ROOT_DIR}/src/swf/PluginExplorerMenu.swf"
		"--translation-files"
			"${ROOT_DIR}/res/${PROJECT_NAME}_CHINESE.txt"
			"${ROOT_DIR}/res/${PROJECT_NAME}_CZECH.txt"
			"${ROOT_DIR}/res/${PROJECT_NAME}_ENGLISH.txt"
			"${ROOT_DIR}/res/${PROJECT_NAME}_FRENCH.txt"
			"${ROOT_DIR}/res/${PROJECT_NAME}_GERMAN.txt"
			"${ROOT_DIR}/res/${PROJECT_NAME}_ITALIAN.txt"
			"${ROOT_DIR}/res/${PROJECT_NAME}_JAPANESE.txt"
			"${ROOT_DIR}/res/${PROJECT_NAME}_POLISH.txt"
			"${ROOT_DIR}/res/${PROJECT_NAME}_RUSSIAN.txt"
			"${ROOT_DIR}/res/${PROJECT_NAME}_SPANISH.txt"
	DEPENDS
		"${PROJECT_NAME}"
	BYPRODUCTS
		"${ROOT_DIR}/build/${ARCHIVE_NAME}.zip"
		"${ROOT_DIR}/build/${ARCHIVE_NAME}_pdb.zip"
	VERBATIM
	SOURCES
		"${SCRIPT}"
)