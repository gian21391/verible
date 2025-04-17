cmake_minimum_required(VERSION 3.20)
set(verible_VERSION 0.1)
project(verible
        VERSION ${verible_VERSION}
        DESCRIPTION ""
        HOMEPAGE_URL "https://github.com/chipsalliance/verible"
        LANGUAGES CXX)

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
        casts logging DPI declaration expression functions module parameters port type verilog-nonterminals with-reason
        verilog-treebuilder-utils token-generator concrete-syntax-tree token-info concrete-syntax-leaf symbol lexer
        visitors iterator-adaptors spacer type-traits verilog-matchers syntax-tree-search symbol-ptr verilog-lexer
        verilog-token-classifications verilog-token-enum identifier constants container-util tree-compare iterator-range
        rebase range auto-iterator matcher-builders bound-symbol-manager syntax-tree-context tree-context-visitor
        descent-path inner-match-handlers matcher auto-pop-stack display-utils verilog-token verilog-tree-json
        token-info-json verilog-tree-print json-diagnostics token-stream-adapter utf8 document-view flex-lexer-adapter
        mem-block file-analyzer line-column-map token-stream-view status-macros bijective-map compare build-version
        parser-verifier comment-utils verilog-lexical-context verilog-preprocess macro-definition lint-rule-registry
        text-structure verilog-filelist lint-rule-status syntax-tree-lint-rule descriptions line-lint-rule package net
        enum-flags text-structure-lint-rule token-stream-lint-rule citation lint-rule statement config-utils tasks
        file-util constraints core-matchers context-functions seq-block verilog-linter-constants dimensions data
        init-command-line naming-utils numbers macro verilog-analyzer verilog-lint-rules always-comb-blocking-rule
        always-comb-rule always-ff-non-blocking-rule banned-declared-name-patterns-rule case-missing-default-rule
        constraint-name-style-rule create-object-name-match-rule dff-name-style-rule disable-statement-rule
        endif-comment-rule enum-name-style-rule explicit-begin-rule explicit-function-lifetime-rule
        explicit-function-task-parameter-type-rule explicit-parameter-storage-type-rule explicit-task-lifetime-rule
        forbid-consecutive-null-statements-rule forbid-defparam-rule forbid-line-continuations-rule
        forbid-negative-array-dim forbidden-anonymous-enums-rule
        forbidden-anonymous-structs-unions-rule forbidden-macro-rule forbidden-symbol-rule generate-label-prefix-rule
        generate-label-rule instance-shadow-rule interface-name-style-rule legacy-generate-region-rule
        legacy-genvar-declaration-rule line-length-rule macro-name-style-rule macro-string-concatenation-rule
        mismatched-labels-rule module-begin-block-rule module-filename-rule module-instantiation-rules
        no-tabs-rule no-trailing-spaces-rule numeric-format-string-style-rule one-module-per-file-rule
        package-filename-rule packed-dimensions-rule parameter-name-style-rule parameter-type-name-style-rule
        plusarg-assignment-rule port-name-suffix-rule positive-meaning-parameter-name-rule posix-eof-rule
        proper-parameter-declaration-rule signal-name-style-rule struct-union-name-style-rule suggest-parentheses-rule
        suspicious-semicolon-rule truncated-numeric-literal-rule undersized-binary-literal-rule
        unpacked-dimensions-rule uvm-macro-semicolon-rule v2001-generate-begin-rule void-cast-rule
        EXPORT verible-targets
        FILE_SET sources DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/verible")
install(DIRECTORY verible/
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/verible
        FILES_MATCHING PATTERN "*.h")
install(FILES
        ${CMAKE_BINARY_DIR}/verible/verilog/parser/verilog-token-enum.h
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/verible/verilog/parser)
install(EXPORT verible-targets
        NAMESPACE verible::
        DESTINATION ${CMAKE_INSTALL_DATADIR}/verible)