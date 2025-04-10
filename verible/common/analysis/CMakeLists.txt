add_library(citation STATIC citation.cc)
add_library(verible::common::analysis::citation ALIAS citation)
target_include_directories(citation PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(citation PUBLIC absl::base)

add_library(lint-rule-status STATIC lint-rule-status.cc)
add_library(verible::common::analysis::lint-rule-status ALIAS lint-rule-status)
target_include_directories(lint-rule-status PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(lint-rule-status PUBLIC
        verible::common::analysis::citation
        verible::common::strings::line-column-map
        verible::common::text::concrete-syntax-leaf
        verible::common::text::symbol
        verible::common::text::syntax-tree-context
        verible::common::text::token-info
        verible::common::text::tree-utils
        verible::common::util::logging
        verible::common::util::spacer
)

add_library(lint-rule INTERFACE)
add_library(verible::common::analysis::lint-rule ALIAS lint-rule)
target_include_directories(lint-rule INTERFACE ${CMAKE_SOURCE_DIR})
target_link_libraries(lint-rule INTERFACE
        verible::common::analysis::lint-rule-status
)

flex_target(command-file-lex
        ${CMAKE_CURRENT_SOURCE_DIR}/command_file.lex
        ${CMAKE_CURRENT_BINARY_DIR}/command-file.yy.cc
)
add_custom_target(command-file-lex-gen DEPENDS
        ${CMAKE_CURRENT_BINARY_DIR}/command-file.yy.cc
)

add_library(command-file-lexer STATIC command-file-lexer.cc ${CMAKE_BINARY_DIR}/verible/common/analysis/command-file.yy.cc)
add_library(verible::common::analysis::command-file-lexer ALIAS command-file-lexer)
target_include_directories(command-file-lexer PUBLIC ${CMAKE_SOURCE_DIR} ${FLEX_INCLUDE_DIR})
target_link_libraries(command-file-lexer PUBLIC
        verible::common::lexer::flex-lexer-adapter
        verible::common::lexer::token-stream-adapter
        verible::common::text::token-info
        verible::common::text::token-stream-view
        verible::common::util::iterator-range
        verible::common::util::logging
)
add_dependencies(command-file-lexer command-file-lex-gen)

add_executable(command-file-lexer_test command-file-lexer_test.cc)
target_link_libraries(command-file-lexer_test PRIVATE
        verible::common::analysis::command-file-lexer
        verible::common::lexer::lexer-test-util
        verible::common::text::constants
        verible::common::text::token-info
        verible::common::text::token-info-test-util
        GTest::gtest
        GTest::gtest_main
)
add_test(NAME command-file-lexer_test COMMAND command-file-lexer_test)

add_library(violation-handler STATIC violation-handler.cc)
add_library(verible::common::analysis::violation-handler ALIAS violation-handler)
target_include_directories(violation-handler PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(violation-handler PUBLIC
        verible::common::analysis::lint-rule-status
        verible::common::strings::diff
        verible::common::util::file-util
        verible::common::util::logging
        verible::common::util::user-interaction
)

add_library(lint-waiver STATIC lint-waiver.cc)
add_library(verible::common::analysis::lint-waiver ALIAS lint-waiver)
target_include_directories(lint-waiver PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(lint-waiver PUBLIC
        verible::common::analysis::command-file-lexer
        verible::common::strings::comment-utils
        verible::common::strings::line-column-map
        verible::common::strings::position
        verible::common::text::text-structure
        verible::common::text::token-info
        verible::common::text::token-stream-view
        verible::common::util::container-iterator-range
        verible::common::util::container-util
        verible::common::util::file-util
        verible::common::util::iterator-range
        verible::common::util::logging
        re2::re2
        absl::flat_hash_map
        absl::statusor
)

add_library(file-analyzer STATIC file-analyzer.cc)
add_library(verible::common::analysis::file-analyzer ALIAS file-analyzer)
target_include_directories(file-analyzer PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(file-analyzer PUBLIC
        verible::common::lexer::token-stream-adapter
        verible::common::parser::parse
        verible::common::strings::line-column-map
        verible::common::strings::mem-block
        verible::common::text::concrete-syntax-tree
        verible::common::text::text-structure
        verible::common::text::token-info
        verible::common::text::token-stream-view
        verible::common::util::logging
        verible::common::util::spacer
)

add_library(linter-test-utils STATIC linter-test-utils.cc)
add_library(verible::common::analysis::linter-test-utils ALIAS linter-test-utils)
target_include_directories(linter-test-utils PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(linter-test-utils PUBLIC
        verible::common::analysis::lint-rule-status
        verible::common::text::token-info
        verible::common::text::token-info-test-util
        verible::common::util::algorithm
        verible::common::util::logging
        GTest::gtest
)

add_library(syntax-tree-search-test-utils STATIC syntax-tree-search-test-utils.cc)
add_library(verible::common::analysis::syntax-tree-search-test-utils ALIAS syntax-tree-search-test-utils)
target_include_directories(syntax-tree-search-test-utils PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(syntax-tree-search-test-utils PUBLIC
        verible::common::analysis::syntax-tree-search
        verible::common::lexer::lexer-test-util
        verible::common::text::token-info
        verible::common::text::token-info-test-util
        verible::common::text::tree-utils
        verible::common::util::algorithm
        verible::common::util::logging
)

add_library(line-linter STATIC line-linter.cc)
add_library(verible::common::analysis::line-linter ALIAS line-linter)
target_include_directories(line-linter PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(line-linter PUBLIC
        verible::common::analysis::line-lint-rule
        verible::common::analysis::lint-rule-status
        verible::common::util::logging
)

add_library(line-linter-test-utils INTERFACE)
add_library(verible::common::analysis::line-linter-test-utils ALIAS line-linter-test-utils)
target_include_directories(line-linter-test-utils INTERFACE ${CMAKE_SOURCE_DIR})
target_link_libraries(line-linter-test-utils INTERFACE
        verible::common::analysis::line-lint-rule
        verible::common::analysis::line-linter
        verible::common::analysis::lint-rule-status
        verible::common::analysis::linter-test-utils
        verible::common::text::text-structure
        verible::common::util::logging
)

add_library(line-lint-rule INTERFACE)
add_library(verible::common::analysis::line-lint-rule ALIAS line-lint-rule)
target_include_directories(line-lint-rule INTERFACE ${CMAKE_SOURCE_DIR})
target_link_libraries(line-lint-rule INTERFACE
        verible::common::analysis::lint-rule
)

add_library(syntax-tree-linter STATIC syntax-tree-linter.cc)
add_library(verible::common::analysis::syntax-tree-linter ALIAS syntax-tree-linter)
target_include_directories(syntax-tree-linter PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(syntax-tree-linter PUBLIC
        verible::common::analysis::lint-rule-status
        verible::common::analysis::syntax-tree-lint-rule
        verible::common::text::concrete-syntax-leaf
        verible::common::text::concrete-syntax-tree
        verible::common::text::symbol
        verible::common::text::tree-context-visitor
        verible::common::util::logging
)

add_library(syntax-tree-linter-test-utils INTERFACE)
add_library(verible::common::analysis::syntax-tree-linter-test-utils ALIAS syntax-tree-linter-test-utils)
target_include_directories(syntax-tree-linter-test-utils INTERFACE ${CMAKE_SOURCE_DIR})
target_link_libraries(syntax-tree-linter-test-utils INTERFACE
        verible::common::analysis::lint-rule-status
        verible::common::analysis::linter-test-utils
        verible::common::analysis::syntax-tree-lint-rule
        verible::common::analysis::syntax-tree-linter
        verible::common::text::text-structure
        verible::common::util::logging
)

add_library(syntax-tree-lint-rule INTERFACE)
add_library(verible::common::analysis::syntax-tree-lint-rule ALIAS syntax-tree-lint-rule)
target_include_directories(syntax-tree-lint-rule INTERFACE ${CMAKE_SOURCE_DIR})
target_link_libraries(syntax-tree-lint-rule INTERFACE
        verible::common::analysis::lint-rule
        verible::common::text::concrete-syntax-leaf
        verible::common::text::concrete-syntax-tree
        verible::common::text::symbol
        verible::common::text::syntax-tree-context
)

add_library(syntax-tree-search STATIC syntax-tree-search.cc)
add_library(verible::common::analysis::syntax-tree-search ALIAS syntax-tree-search)
target_include_directories(syntax-tree-search PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(syntax-tree-search PUBLIC
        verible::common::analysis::matcher::bound-symbol-manager
        verible::common::text::concrete-syntax-leaf
        verible::common::text::concrete-syntax-tree
        verible::common::text::symbol
        verible::common::text::syntax-tree-context
        verible::common::text::tree-context-visitor
)

add_library(text-structure-linter STATIC text-structure-linter.cc)
add_library(verible::common::analysis::text-structure-linter ALIAS text-structure-linter)
target_include_directories(text-structure-linter PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(text-structure-linter PUBLIC
        verible::common::analysis::lint-rule-status
        verible::common::analysis::text-structure-lint-rule
        verible::common::text::text-structure
        verible::common::util::logging
)

add_library(text-structure-linter-test-utils INTERFACE)
add_library(verible::common::analysis::text-structure-linter-test-utils ALIAS text-structure-linter-test-utils)
target_include_directories(text-structure-linter-test-utils INTERFACE ${CMAKE_SOURCE_DIR})
target_link_libraries(text-structure-linter-test-utils INTERFACE
        verible::common::analysis::lint-rule-status
        verible::common::analysis::linter-test-utils
        verible::common::analysis::text-structure-lint-rule
        verible::common::analysis::text-structure-linter
        verible::common::text::text-structure
        verible::common::util::logging
)

add_library(text-structure-lint-rule INTERFACE)
add_library(verible::common::analysis::text-structure-lint-rule ALIAS text-structure-lint-rule)
target_include_directories(text-structure-lint-rule INTERFACE ${CMAKE_SOURCE_DIR})
target_link_libraries(text-structure-lint-rule INTERFACE
        verible::common::analysis::lint-rule
        verible::common::text::text-structure
)

add_library(token-stream-linter STATIC token-stream-linter.cc)
add_library(verible::common::analysis::token-stream-linter ALIAS token-stream-linter)
target_include_directories(token-stream-linter PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(token-stream-linter PUBLIC
        verible::common::analysis::lint-rule-status
        verible::common::analysis::token-stream-lint-rule
        verible::common::text::token-stream-view
        verible::common::util::logging
)

add_library(token-stream-linter-test-utils INTERFACE)
add_library(verible::common::analysis::token-stream-linter-test-utils ALIAS token-stream-linter-test-utils)
target_include_directories(token-stream-linter-test-utils INTERFACE ${CMAKE_SOURCE_DIR})
target_link_libraries(token-stream-linter-test-utils INTERFACE
        verible::common::analysis::lint-rule-status
        verible::common::analysis::linter-test-utils
        verible::common::analysis::token-stream-lint-rule
        verible::common::analysis::token-stream-linter
        verible::common::text::text-structure
        verible::common::util::logging
)

add_library(token-stream-lint-rule INTERFACE)
add_library(verible::common::analysis::token-stream-lint-rule ALIAS token-stream-lint-rule)
target_include_directories(token-stream-lint-rule INTERFACE ${CMAKE_SOURCE_DIR})
target_link_libraries(token-stream-lint-rule INTERFACE
        verible::common::analysis::lint-rule
        verible::common::text::token-info
)

add_executable(lint-rule-status_test lint-rule-status_test.cc)
target_link_libraries(lint-rule-status_test PRIVATE
        verible::common::analysis::lint-rule-status
        verible::common::text::concrete-syntax-tree
        verible::common::text::token-info
        verible::common::text::tree-builder-test-util
        absl::strings
        GTest::gtest
        GTest::gtest_main
)
add_test(NAME lint-rule-status_test COMMAND lint-rule-status_test)

add_executable(lint-waiver_test lint-waiver_test.cc)
target_link_libraries(lint-waiver_test PRIVATE
        verible::common::analysis::lint-waiver
        verible::common::strings::line-column-map
        verible::common::text::text-structure-test-utils
        verible::common::text::token-info
        verible::common::text::token-stream-view
        verible::common::util::iterator-range
        GTest::gtest
        GTest::gtest_main
)
add_test(NAME lint-waiver_test COMMAND lint-waiver_test)

add_executable(file-analyzer_test file-analyzer_test.cc)
target_link_libraries(file-analyzer_test PRIVATE
        verible::common::analysis::file-analyzer
        verible::common::strings::line-column-map
        verible::common::text::text-structure
        verible::common::text::token-info
        absl::status
        absl::strings
        GTest::gtest
        GTest::gtest_main
)
add_test(NAME file-analyzer_test COMMAND file-analyzer_test)

add_executable(linter-test-utils_test linter-test-utils_test.cc)
target_link_libraries(linter-test-utils_test PRIVATE
        verible::common::analysis::lint-rule-status
        verible::common::analysis::linter-test-utils
        verible::common::util::range
        absl::strings
        GTest::gtest
        GTest::gtest_main
)
add_test(NAME linter-test-utils_test COMMAND linter-test-utils_test)

add_executable(line-linter_test line-linter_test.cc)
target_link_libraries(line-linter_test PRIVATE
        verible::common::analysis::line-lint-rule
        verible::common::analysis::line-linter
        verible::common::analysis::lint-rule-status
        verible::common::text::token-info
        absl::status
        absl::log
        GTest::gtest
        GTest::gtest_main
)
add_test(NAME line-linter_test COMMAND line-linter_test)

add_executable(syntax-tree-linter_test syntax-tree-linter_test.cc)
target_link_libraries(syntax-tree-linter_test PRIVATE
        verible::common::analysis::lint-rule-status
        verible::common::analysis::syntax-tree-lint-rule
        verible::common::analysis::syntax-tree-linter
        verible::common::text::concrete-syntax-leaf
        verible::common::text::concrete-syntax-tree
        verible::common::text::symbol
        verible::common::text::syntax-tree-context
        verible::common::text::token-info
        verible::common::text::tree-builder-test-util
        verible::common::util::casts
        absl::status
        GTest::gtest
        GTest::gtest_main
)
add_test(NAME syntax-tree-linter_test COMMAND syntax-tree-linter_test)

add_executable(syntax-tree-search_test syntax-tree-search_test.cc)
target_link_libraries(syntax-tree-search_test PRIVATE
        verible::common::analysis::syntax-tree-search
        verible::common::analysis::matcher::matcher-builders
        verible::common::text::symbol
        verible::common::text::syntax-tree-context
        verible::common::text::tree-builder-test-util
        verible::common::text::tree-utils
        GTest::gtest
        GTest::gtest_main
)
add_test(NAME syntax-tree-search_test COMMAND syntax-tree-search_test)

add_executable(syntax-tree-search-test-utils_test syntax-tree-search-test-utils_test.cc)
target_link_libraries(syntax-tree-search-test-utils_test PRIVATE
        verible::common::analysis::syntax-tree-search
        verible::common::analysis::syntax-tree-search-test-utils
        verible::common::text::tree-builder-test-util
        verible::common::util::range
        absl::strings
        GTest::gtest
        GTest::gtest_main
)
add_test(NAME syntax-tree-search-test-utils_test COMMAND syntax-tree-search-test-utils_test)

add_executable(text-structure-linter_test text-structure-linter_test.cc)
target_link_libraries(text-structure-linter_test PRIVATE
        verible::common::analysis::lint-rule-status
        verible::common::analysis::text-structure-lint-rule
        verible::common::analysis::text-structure-linter
        verible::common::text::text-structure
        verible::common::text::token-info
        absl::strings
        GTest::gtest
        GTest::gtest_main
)
add_test(NAME text-structure-linter_test COMMAND text-structure-linter_test)

add_executable(token-stream-linter_test token-stream-linter_test.cc)
target_link_libraries(token-stream-linter_test PRIVATE
        verible::common::analysis::lint-rule-status
        verible::common::analysis::token-stream-lint-rule
        verible::common::analysis::token-stream-linter
        verible::common::text::token-info
        verible::common::text::token-stream-view
        absl::status
        GTest::gtest
        GTest::gtest_main
)
add_test(NAME token-stream-linter_test COMMAND token-stream-linter_test)
