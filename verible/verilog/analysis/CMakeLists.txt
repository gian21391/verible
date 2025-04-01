add_library(default-rules INTERFACE)
add_library(verible::verilog::analysis::default-rules ALIAS default-rules)
target_include_directories(default-rules INTERFACE ${CMAKE_SOURCE_DIR})
target_link_libraries(default-rules INTERFACE
  verible::verilog::analysis::checkers::verilog-lint-rules
)

add_library(descriptions INTERFACE)
add_library(verible::verilog::analysis::descriptions ALIAS descriptions)
target_include_directories(descriptions INTERFACE ${CMAKE_SOURCE_DIR})

add_library(extractors STATIC extractors.cc)
add_library(verible::verilog::analysis::extractors ALIAS extractors)
target_include_directories(extractors PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(extractors PUBLIC
  verible::verilog::analysis::verilog-analyzer
  verible::common::text::tree-utils
  verible::common::util::logging
  verible::verilog::CST::identifier
  verible::verilog::CST::module
  verible::verilog::preprocessor::verilog-preprocess
)

add_library(json-diagnostics STATIC json-diagnostics.cc)
add_library(verible::verilog::analysis::json-diagnostics ALIAS json-diagnostics)
target_include_directories(json-diagnostics PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(json-diagnostics PUBLIC
  verible::verilog::analysis::verilog-analyzer
  verible::common::analysis::file-analyzer
  verible::common::strings::line-column-map
  nlohmann_json::nlohmann_json
)

add_library(flow-tree STATIC flow-tree.cc)
add_library(verible::verilog::analysis::flow-tree ALIAS flow-tree)
target_include_directories(flow-tree PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(flow-tree PUBLIC
  verible::common::text::token-stream-view
  verible::common::util::logging
  verible::verilog::parser::verilog-token-enum
)

add_library(lint-rule-registry STATIC lint-rule-registry.cc)
add_library(verible::verilog::analysis::lint-rule-registry ALIAS lint-rule-registry)
target_include_directories(lint-rule-registry PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(lint-rule-registry PUBLIC
  verible::verilog::analysis::descriptions
  verible::common::analysis::line-lint-rule
  verible::common::analysis::syntax-tree-lint-rule
  verible::common::analysis::text-structure-lint-rule
  verible::common::analysis::token-stream-lint-rule
  verible::common::strings::compare
  verible::common::util::container-util
  verible::common::util::logging
  absl::node_hash_map
)

add_library(verilog-analyzer STATIC verilog-analyzer.cc verilog-excerpt-parse.cc)
add_library(verible::verilog::analysis::verilog-analyzer ALIAS verilog-analyzer)
target_include_directories(verilog-analyzer PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(verilog-analyzer PUBLIC
  verible::common::analysis::file-analyzer
  verible::common::lexer::token-stream-adapter
  verible::common::strings::comment-utils
  verible::common::strings::mem-block
  verible::common::text::concrete-syntax-leaf
  verible::common::text::concrete-syntax-tree
  verible::common::text::symbol
  verible::common::text::text-structure
  verible::common::text::token-info
  verible::common::text::token-stream-view
  verible::common::text::visitors
  verible::common::util::container-util
  verible::common::util::logging
  verible::common::util::status-macros
  verible::verilog::parser::verilog-lexer
  verible::verilog::parser::verilog-lexical-context
  verible::verilog::parser::verilog-parser
  verible::verilog::parser::verilog-token-classifications
  verible::verilog::parser::verilog-token-enum
  verible::verilog::preprocessor::verilog-preprocess
  absl::config
)

add_library(verilog-equivalence STATIC verilog-equivalence.cc)
add_library(verible::verilog::analysis::verilog-equivalence ALIAS verilog-equivalence)
target_include_directories(verilog-equivalence PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(verilog-equivalence PUBLIC
  verible::common::lexer::token-stream-adapter
  verible::common::text::token-info
  verible::common::text::token-stream-view
  verible::common::util::enum-flags
  verible::common::util::logging
  verible::verilog::parser::verilog-lexer
  verible::verilog::parser::verilog-parser
  verible::verilog::parser::verilog-token-classifications
  verible::verilog::parser::verilog-token-enum
)

add_library(verilog-linter-configuration STATIC verilog-linter-configuration.cc)
add_library(verible::verilog::analysis::verilog-linter-configuration ALIAS verilog-linter-configuration)
target_include_directories(verilog-linter-configuration PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(verilog-linter-configuration PUBLIC
  verible::verilog::analysis::default-rules
  verible::verilog::analysis::descriptions
  verible::verilog::analysis::lint-rule-registry
  verible::common::analysis::line-lint-rule
  verible::common::analysis::syntax-tree-lint-rule
  verible::common::analysis::text-structure-lint-rule
  verible::common::analysis::token-stream-lint-rule
  verible::common::util::container-util
  verible::common::util::enum-flags
  verible::common::util::file-util
  verible::common::util::logging
  verible::common::util::status-macros
  absl::statusor
)

add_library(verilog-linter-constants INTERFACE)
add_library(verible::verilog::analysis::verilog-linter-constants ALIAS verilog-linter-constants)
target_include_directories(verilog-linter-constants INTERFACE ${CMAKE_SOURCE_DIR})

add_library(verilog-linter STATIC verilog-linter.cc)
add_library(verible::verilog::analysis::verilog-linter ALIAS verilog-linter)
target_include_directories(verilog-linter PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(verilog-linter PUBLIC
  verible::verilog::analysis::default-rules
  verible::verilog::analysis::lint-rule-registry
  verible::verilog::analysis::verilog-analyzer
  verible::verilog::analysis::verilog-linter-configuration
  verible::verilog::analysis::verilog-linter-constants
  verible::common::analysis::citation
  verible::common::analysis::line-linter
  verible::common::analysis::lint-rule-status
  verible::common::analysis::lint-waiver
  verible::common::analysis::syntax-tree-linter
  verible::common::analysis::text-structure-linter
  verible::common::analysis::token-stream-linter
  verible::common::analysis::violation-handler
  verible::common::strings::line-column-map
  verible::common::text::concrete-syntax-tree
  verible::common::text::text-structure
  verible::common::text::token-info
  verible::common::util::file-util
  verible::common::util::logging
  verible::common::util::status-macros
  verible::verilog::parser::verilog-token-classifications
  verible::verilog::parser::verilog-token-enum
  absl::config
  absl_flag
  absl::statusor
)

add_library(verilog-filelist STATIC verilog-filelist.cc)
add_library(verible::verilog::analysis::verilog-filelist ALIAS verilog-filelist)
target_include_directories(verilog-filelist PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(verilog-filelist PUBLIC
  verible::common::util::file-util
  verible::common::util::iterator-range
)

add_library(verilog-project STATIC verilog-project.cc)
add_library(verible::verilog::analysis::verilog-project ALIAS verilog-project)
target_include_directories(verilog-project PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(verilog-project PUBLIC
  verible::verilog::analysis::verilog-analyzer
  verible::common::strings::mem-block
  verible::common::strings::string-memory-map
  verible::common::text::text-structure
  verible::common::util::file-util
  verible::common::util::logging
  absl::statusor
  absl::optional
)

add_library(symbol-table STATIC symbol-table.cc)
add_library(verible::verilog::analysis::symbol-table ALIAS symbol-table)
target_include_directories(symbol-table PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(symbol-table PUBLIC
  verible::verilog::analysis::verilog-project
  verible::common::strings::compare
  verible::common::strings::display-utils
  verible::common::text::concrete-syntax-leaf
  verible::common::text::concrete-syntax-tree
  verible::common::text::symbol
  verible::common::text::token-info
  verible::common::text::tree-compare
  verible::common::text::tree-context-visitor
  verible::common::text::tree-utils
  verible::common::text::visitors
  verible::common::util::casts
  verible::common::util::enum-flags
  verible::common::util::logging
  verible::common::util::map-tree
  verible::common::util::spacer
  verible::common::util::tree-operations
  verible::common::util::value-saver
  verible::common::util::vector-tree
  verible::verilog::CST::class
  verible::verilog::CST::declaration
  verible::verilog::CST::functions
  verible::verilog::CST::macro
  verible::verilog::CST::module
  verible::verilog::CST::net
  verible::verilog::CST::package
  verible::verilog::CST::parameters
  verible::verilog::CST::port
  verible::verilog::CST::seq-block
  verible::verilog::CST::statement
  verible::verilog::CST::tasks
  verible::verilog::CST::type
  verible::verilog::CST::verilog-nonterminals
  verible::verilog::parser::verilog-parser
  verible::verilog::parser::verilog-token-enum
  absl::statusor
)

add_library(dependencies STATIC dependencies.cc)
add_library(verible::verilog::analysis::dependencies ALIAS dependencies)
target_include_directories(dependencies PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(dependencies PUBLIC
  verible::verilog::analysis::symbol-table
  verible::verilog::analysis::verilog-project
  verible::common::strings::compare
  verible::common::strings::display-utils
  verible::common::util::logging
)

