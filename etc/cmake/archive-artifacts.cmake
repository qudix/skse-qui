find_package(
	Python3
	MODULE
	REQUIRED
	COMPONENTS
		Interpreter
)

set(SCRIPT "${ROOT_DIR}/etc/scripts/archive-artifacts.py")

if("${USE_AE}")
	set(ARCHIVE_NAME "${PROJECT_NAME}-AE-${PROJECT_VERSION}")
else()
	set(ARCHIVE_NAME "${PROJECT_NAME}-${PROJECT_VERSION}")
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
            "${ROOT_DIR}/src/swf/StartMenuEx.swf"
	DEPENDS
		"${PROJECT_NAME}"
	BYPRODUCTS
		"${ROOT_DIR}/bin/${ARCHIVE_NAME}.zip"
		"${ROOT_DIR}/bin/${ARCHIVE_NAME}.pdb.zip"
	VERBATIM
	SOURCES
		"${SCRIPT}"
)