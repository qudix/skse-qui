# header-only library
vcpkg_from_github(
    OUT_SOURCE_PATH SOURCE_PATH
    REPO powerof3/CLibUtil
    REF 6f430ac180ba0e64128bba8d632c20367833c5ef
    SHA512 f215021022db502069fcca8089c045aebce2ba4ff7e8eda0f9a4dbbd3db0b2eb7b11b224e7ec59c31e44d223dfaa1c4bab53104ac5d62b9b6b909013e9142d00
    HEAD_REF master
)

# Install codes
set(CLIBUTIL_SOURCE	${SOURCE_PATH}/include/ClibUtil)
file(INSTALL ${CLIBUTIL_SOURCE} DESTINATION ${CURRENT_PACKAGES_DIR}/include)

vcpkg_install_copyright(FILE_LIST "${SOURCE_PATH}/LICENSE")