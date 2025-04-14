cmake_minimum_required(VERSION 3.20)
set(verible_VERSION 0.1)
project(verible
        VERSION ${verible_VERSION}
        DESCRIPTION ""
        HOMEPAGE_URL "https://github.com/chipsalliance/verible"
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

if(WIN32)
    find_package(BISON)
    if(NOT BISON_FOUND)
        include(FetchContent)
        FetchContent_Declare(win_flex_bison
                URL https://github.com/lexxmark/winflexbison/releases/download/v2.5.25/win_flex_bison-2.5.25.zip
                URL_MD5 720226b1befe7033fb3ecc98f5ffd425
                DOWNLOAD_EXTRACT_TIMESTAMP TRUE
        )
        FetchContent_MakeAvailable(win_flex_bison)
        LIST(APPEND CMAKE_PROGRAM_PATH "${win_flex_bison_SOURCE_DIR}")
    endif ()
endif ()

find_package(FLEX REQUIRED)
find_package(BISON REQUIRED)
cmake_path(GET FLEX_EXECUTABLE PARENT_PATH FLEX_INCLUDE_DIR)

include(cmake/targets.cmake)
include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

option(VERIBLE_TEST "Generate the test targets." ON)
if (VERIBLE_TEST)
    message("Testing enabled")
    include(CTest)
    find_package(GTest CONFIG REQUIRED)
endif ()

find_package(absl CONFIG REQUIRED)
find_package(re2 CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(ZLIB REQUIRED)
find_package(Python3 REQUIRED COMPONENTS Interpreter)

add_subdirectory(external_libs)
add_subdirectory(third_party/portable_endian)
add_subdirectory(verible)

configure_package_config_file(cmake/config.cmake.in
        ${CMAKE_CURRENT_BINARY_DIR}/verible-config.cmake
        INSTALL_DESTINATION ${CMAKE_INSTALL_DATADIR}/verible
        NO_SET_AND_CHECK_MACRO)
write_basic_package_version_file(
        ${CMAKE_CURRENT_BINARY_DIR}/verible-config-version.cmake
        VERSION ${verible_VERSION}
        COMPATIBILITY SameMajorVersion)
install(FILES
        ${CMAKE_CURRENT_BINARY_DIR}/verible-config.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/verible-config-version.cmake
        DESTINATION ${CMAKE_INSTALL_DATADIR}/verible)
install(TARGETS
        verilog-parser verilog-y-cc bison-parser-adapter parse parser-param value-saver bison-parser-common tree-utils
        casts logging DPI declaration expression functions module parameters port type verilog-nonterminals
        verilog-treebuilder-utils token-generator concrete-syntax-tree token-info concrete-syntax-leaf symbol
        visitors iterator-adaptors spacer type-traits verilog-matchers syntax-tree-search symbol-ptr
        verilog-token-classifications verilog-token-enum identifier constants container-util tree-compare iterator-range
        rebase range auto-iterator matcher-builders bound-symbol-manager syntax-tree-context tree-context-visitor
        descent-path inner-match-handlers matcher auto-pop-stack display-utils
        EXPORT verible-targets)
install(DIRECTORY verible/
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
        FILES_MATCHING PATTERN "*.h")
install(EXPORT verible-targets
        NAMESPACE verible::
        DESTINATION ${CMAKE_INSTALL_DATADIR}/verible)