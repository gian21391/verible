add_library(token-info STATIC token-info.cc)
add_library(verible::common::text::token-info ALIAS token-info)
target_include_directories(token-info PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(token-info PUBLIC
        verible::common::text::constants
        verible::common::strings::rebase
        verible::common::util::iterator-range
        verible::common::util::logging
        verible::common::util::range
        absl::strings
)

add_library(token-info-json STATIC token-info-json.cc)
add_library(verible::common::text::token-info-json ALIAS token-info-json)
target_include_directories(token-info-json PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(token-info-json PUBLIC
        verible::common::text::token-info
        nlohmann_json::nlohmann_json
)

add_library(token-info-test-util STATIC token-info-test-util.cc)
add_library(verible::common::text::token-info-test-util ALIAS token-info-test-util)
target_include_directories(token-info-test-util PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(token-info-test-util PUBLIC
        verible::common::text::token-info
        verible::common::util::logging
)

add_library(token-stream-view STATIC token-stream-view.cc)
add_library(verible::common::text::token-stream-view ALIAS token-stream-view)
target_include_directories(token-stream-view PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(token-stream-view PUBLIC
        verible::common::text::token-info
        verible::common::util::iterator-range
)

add_library(symbol-ptr INTERFACE)
add_library(verible::common::text::symbol-ptr ALIAS symbol-ptr)
target_include_directories(symbol-ptr INTERFACE ${CMAKE_SOURCE_DIR})

add_library(symbol STATIC symbol.cc)
add_library(verible::common::text::symbol ALIAS symbol)
target_include_directories(symbol PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(symbol PUBLIC
        verible::common::text::symbol-ptr
        verible::common::text::token-info
        verible::common::text::visitors
)

add_library(concrete-syntax-leaf STATIC concrete-syntax-leaf.cc)
add_library(verible::common::text::concrete-syntax-leaf ALIAS concrete-syntax-leaf)
target_include_directories(concrete-syntax-leaf PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(concrete-syntax-leaf PUBLIC
        verible::common::text::concrete-syntax-tree
        verible::common::text::symbol
        verible::common::text::token-info
        verible::common::text::tree-compare
        verible::common::text::visitors
        verible::common::util::casts
        verible::common::util::logging
)

add_library(concrete-syntax-tree STATIC concrete-syntax-tree.cc)
add_library(verible::common::text::concrete-syntax-tree ALIAS concrete-syntax-tree)
target_include_directories(concrete-syntax-tree PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(concrete-syntax-tree PUBLIC
        verible::common::text::constants
        verible::common::text::symbol
        verible::common::text::symbol-ptr
        verible::common::text::tree-compare
        verible::common::text::visitors
        verible::common::util::casts
        verible::common::util::iterator-range
        verible::common::util::logging
        absl::core_headers
)

add_library(config-utils STATIC config-utils.cc)
add_library(verible::common::text::config-utils ALIAS config-utils)
target_include_directories(config-utils PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(config-utils PUBLIC
        verible::common::util::logging
        absl::status
        absl::strings
        re2::re2
)

add_library(visitors INTERFACE)
add_library(verible::common::text::visitors ALIAS visitors)
target_include_directories(visitors INTERFACE ${CMAKE_SOURCE_DIR})
target_link_libraries(visitors INTERFACE
        verible::common::text::symbol-ptr
)

add_library(syntax-tree-context INTERFACE)
add_library(verible::common::text::syntax-tree-context ALIAS syntax-tree-context)
target_include_directories(syntax-tree-context INTERFACE ${CMAKE_SOURCE_DIR})
target_link_libraries(syntax-tree-context INTERFACE
        verible::common::text::concrete-syntax-tree
        verible::common::util::auto-pop-stack
        verible::common::util::iterator-adaptors
        verible::common::util::logging
)

add_library(tree-compare STATIC tree-compare.cc)
add_library(verible::common::text::tree-compare ALIAS tree-compare)
target_include_directories(tree-compare PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(tree-compare PUBLIC
        verible::common::text::symbol
        verible::common::text::token-info
)

add_library(tree-context-visitor STATIC tree-context-visitor.cc)
add_library(verible::common::text::tree-context-visitor ALIAS tree-context-visitor)
target_include_directories(tree-context-visitor PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(tree-context-visitor PUBLIC
        verible::common::text::concrete-syntax-tree
        verible::common::text::syntax-tree-context
        verible::common::text::visitors
        verible::common::strings::display-utils
        verible::common::util::logging
)

add_library(tree-utils STATIC tree-utils.cc)
add_library(verible::common::text::tree-utils ALIAS tree-utils)
target_include_directories(tree-utils PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(tree-utils PUBLIC
        verible::common::text::concrete-syntax-leaf
        verible::common::text::concrete-syntax-tree
        verible::common::text::symbol
        verible::common::text::token-info
        verible::common::text::visitors
        verible::common::util::casts
        verible::common::util::iterator-adaptors
        verible::common::util::logging
        verible::common::util::spacer
        verible::common::util::type-traits
        verible::common::util::value-saver
        absl::base
)

add_library(tree-builder-test-util STATIC tree-builder-test-util.cc)
add_library(verible::common::text::tree-builder-test-util ALIAS tree-builder-test-util)
target_include_directories(tree-builder-test-util PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(tree-builder-test-util PUBLIC
        verible::common::text::concrete-syntax-leaf
        verible::common::text::concrete-syntax-tree
        verible::common::text::symbol
        verible::common::text::tree-utils
        verible::common::util::logging
)

add_library(text-structure STATIC text-structure.cc)
add_library(verible::common::text::text-structure ALIAS text-structure)
target_include_directories(text-structure PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(text-structure PUBLIC
        verible::common::text::concrete-syntax-leaf
        verible::common::text::concrete-syntax-tree
        verible::common::text::symbol
        verible::common::text::token-info
        verible::common::text::token-stream-view
        verible::common::text::tree-utils
        verible::common::strings::line-column-map
        verible::common::strings::mem-block
        verible::common::util::iterator-range
        verible::common::util::logging
        verible::common::util::range
        verible::common::util::status-macros
        absl::status
        absl::strings
)

add_library(text-structure-test-utils STATIC text-structure-test-utils.cc)
add_library(verible::common::text::text-structure-test-utils ALIAS text-structure-test-utils)
target_include_directories(text-structure-test-utils PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(text-structure-test-utils PUBLIC
        verible::common::text::concrete-syntax-tree
        verible::common::text::text-structure
        verible::common::text::token-info
        verible::common::text::token-stream-view
        verible::common::text::tree-builder-test-util
        verible::common::util::logging
        absl::strings
)

add_library(macro-definition STATIC macro-definition.cc)
add_library(verible::common::text::macro-definition ALIAS macro-definition)
target_include_directories(macro-definition PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(macro-definition PUBLIC
        verible::common::text::token-info
        verible::common::util::container-util
        absl::status
        absl::strings
)

add_library(parser-verifier STATIC parser-verifier.cc)
add_library(verible::common::text::parser-verifier ALIAS parser-verifier)
target_include_directories(parser-verifier PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(parser-verifier PUBLIC
        verible::common::text::concrete-syntax-leaf
        verible::common::text::concrete-syntax-tree
        verible::common::text::symbol
        verible::common::text::token-info
        verible::common::text::token-stream-view
        verible::common::text::tree-compare
        verible::common::text::visitors
)

add_library(constants INTERFACE)
add_library(verible::common::text::constants ALIAS constants)
target_include_directories(constants INTERFACE ${CMAKE_SOURCE_DIR})

add_executable(concrete-syntax-leaf_test concrete-syntax-leaf_test.cc)
target_link_libraries(concrete-syntax-leaf_test PRIVATE
        verible::common::text::concrete-syntax-leaf
        verible::common::text::token-info
        GTest::gtest
        GTest::gtest_main
)
add_test(NAME concrete-syntax-leaf_test COMMAND concrete-syntax-leaf_test)

add_executable(config-utils_test config-utils_test.cc)
target_link_libraries(config-utils_test PRIVATE
        verible::common::text::config-utils
        absl::status
        absl::strings
        GTest::gtest
        GTest::gtest_main
        re2::re2
)
add_test(NAME config-utils_test COMMAND config-utils_test)

add_executable(tree-compare_test tree-compare_test.cc)
target_link_libraries(tree-compare_test PRIVATE
        verible::common::text::concrete-syntax-tree
        verible::common::text::tree-builder-test-util
        verible::common::text::tree-compare
        GTest::gtest
        GTest::gtest_main
)
add_test(NAME tree-compare_test COMMAND tree-compare_test)

add_executable(tree-context-visitor_test tree-context-visitor_test.cc)
target_link_libraries(tree-context-visitor_test PRIVATE
        verible::common::text::concrete-syntax-leaf
        verible::common::text::concrete-syntax-tree
        verible::common::text::symbol-ptr
        verible::common::text::syntax-tree-context
        verible::common::text::tree-builder-test-util
        verible::common::text::tree-context-visitor
        GTest::gtest
        GTest::gtest_main
)
add_test(NAME tree-context-visitor_test COMMAND tree-context-visitor_test)

add_executable(tree-builder-test-util_test tree-builder-test-util_test.cc)
target_link_libraries(tree-builder-test-util_test PRIVATE
        verible::common::text::symbol-ptr
        verible::common::text::tree-builder-test-util
        verible::common::text::tree-utils
        GTest::gtest
        GTest::gtest_main
)
add_test(NAME tree-builder-test-util_test COMMAND tree-builder-test-util_test)

add_executable(tree-utils_test tree-utils_test.cc)
target_link_libraries(tree-utils_test PRIVATE
        verible::common::text::concrete-syntax-leaf
        verible::common::text::concrete-syntax-tree
        verible::common::text::symbol
        verible::common::text::token-info
        verible::common::text::tree-builder-test-util
        verible::common::text::tree-compare
        verible::common::text::tree-utils
        verible::common::util::casts
        verible::common::util::logging
        verible::common::util::range
        GTest::gtest
        GTest::gtest_main
)
add_test(NAME tree-utils_test COMMAND tree-utils_test)

add_executable(concrete-syntax-tree_test concrete-syntax-tree_test.cc)
target_link_libraries(concrete-syntax-tree_test PRIVATE
        verible::common::text::concrete-syntax-leaf
        verible::common::text::concrete-syntax-tree
        verible::common::text::symbol
        verible::common::text::tree-builder-test-util
        verible::common::text::tree-compare
        verible::common::util::casts
        verible::common::util::logging
        GTest::gtest
        GTest::gtest_main
)
add_test(NAME concrete-syntax-tree_test COMMAND concrete-syntax-tree_test)

add_executable(token-info_test token-info_test.cc)
target_link_libraries(token-info_test PRIVATE
        verible::common::text::constants
        verible::common::text::token-info
        verible::common::util::range
        GTest::gtest
        GTest::gtest_main
)
add_test(NAME token-info_test COMMAND token-info_test)

add_executable(token-info-json_test token-info-json_test.cc)
target_link_libraries(token-info-json_test PRIVATE
        verible::common::text::constants
        verible::common::text::token-info
        verible::common::text::token-info-json
        GTest::gtest
        GTest::gtest_main
        nlohmann_json::nlohmann_json
)
add_test(NAME token-info-json_test COMMAND token-info-json_test)

add_executable(token-info-test-util_test token-info-test-util_test.cc)
target_link_libraries(token-info-test-util_test PRIVATE
        verible::common::text::token-info
        verible::common::text::token-info-test-util
        GTest::gtest
        GTest::gtest_main
)
add_test(NAME token-info-test-util_test COMMAND token-info-test-util_test)

add_executable(token-stream-view_test token-stream-view_test.cc)
target_link_libraries(token-stream-view_test PRIVATE
        verible::common::text::text-structure
        verible::common::text::text-structure-test-utils
        verible::common::text::token-info
        verible::common::text::token-stream-view
        verible::common::util::iterator-range
        GTest::gtest
        GTest::gtest_main
)
add_test(NAME token-stream-view_test COMMAND token-stream-view_test)

add_executable(syntax-tree-context_test syntax-tree-context_test.cc)
target_link_libraries(syntax-tree-context_test PRIVATE
        verible::common::text::concrete-syntax-tree
        verible::common::text::syntax-tree-context
        verible::common::util::iterator-range
        GTest::gtest
        GTest::gtest_main
)
add_test(NAME syntax-tree-context_test COMMAND syntax-tree-context_test)

add_executable(text-structure_test text-structure_test.cc)
target_link_libraries(text-structure_test PRIVATE
        verible::common::text::concrete-syntax-tree
        verible::common::text::constants
        verible::common::text::symbol
        verible::common::text::text-structure
        verible::common::text::text-structure-test-utils
        verible::common::text::token-info
        verible::common::text::token-stream-view
        verible::common::text::tree-builder-test-util
        verible::common::text::tree-compare
        verible::common::strings::line-column-map
        verible::common::util::casts
        verible::common::util::iterator-range
        verible::common::util::logging
        verible::common::util::range
        verible::common::util::value-saver
        absl::base
        GTest::gtest
        GTest::gtest_main
)
add_test(NAME text-structure_test COMMAND text-structure_test)

add_executable(macro-definition_test macro-definition_test.cc)
target_link_libraries(macro-definition_test PRIVATE
        verible::common::text::macro-definition
        verible::common::text::token-info
        verible::common::util::container-util
        absl::base
        GTest::gtest
        GTest::gtest_main
)
add_test(NAME macro-definition_test COMMAND macro-definition_test)

add_executable(parser-verifier_test parser-verifier_test.cc)
target_link_libraries(parser-verifier_test PRIVATE
        verible::common::text::constants
        verible::common::text::parser-verifier
        verible::common::text::token-info
        verible::common::text::token-stream-view
        verible::common::text::tree-builder-test-util
        GTest::gtest
        GTest::gtest_main
)
add_test(NAME parser-verifier_test COMMAND parser-verifier_test)