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

add_library(command-file-lexer INTERFACE)
add_library(verible::common::analysis::command-file-lexer ALIAS command-file-lexer)
target_include_directories(command-file-lexer INTERFACE ${CMAKE_SOURCE_DIR} ${FLEX_INCLUDE_DIR})
target_link_libraries(command-file-lexer INTERFACE
        verible::common::lexer::flex-lexer-adapter
        verible::common::lexer::token-stream-adapter
        verible::common::text::token-info
        verible::common::text::token-stream-view
        verible::common::util::iterator-range
        verible::common::util::logging
)

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