add_library(verilog-lint-rules INTERFACE)
add_library(verible::verilog::analysis::checkers::verilog-lint-rules ALIAS verilog-lint-rules)
target_include_directories(verilog-lint-rules INTERFACE ${CMAKE_SOURCE_DIR})
target_link_libraries(verilog-lint-rules INTERFACE
  verible::verilog::analysis::checkers::always-comb-blocking-rule
  verible::verilog::analysis::checkers::always-comb-rule
  verible::verilog::analysis::checkers::always-ff-non-blocking-rule
  verible::verilog::analysis::checkers::banned-declared-name-patterns-rule
  verible::verilog::analysis::checkers::case-missing-default-rule
  verible::verilog::analysis::checkers::constraint-name-style-rule
  verible::verilog::analysis::checkers::create-object-name-match-rule
  verible::verilog::analysis::checkers::dff-name-style-rule
  verible::verilog::analysis::checkers::disable-statement-rule
  verible::verilog::analysis::checkers::endif-comment-rule
  verible::verilog::analysis::checkers::enum-name-style-rule
  verible::verilog::analysis::checkers::explicit-begin-rule
  verible::verilog::analysis::checkers::explicit-function-lifetime-rule
  verible::verilog::analysis::checkers::explicit-function-task-parameter-type-rule
  verible::verilog::analysis::checkers::explicit-parameter-storage-type-rule
  verible::verilog::analysis::checkers::explicit-task-lifetime-rule
  verible::verilog::analysis::checkers::forbid-consecutive-null-statements-rule
  verible::verilog::analysis::checkers::forbid-defparam-rule
  verible::verilog::analysis::checkers::forbid-line-continuations-rule
  verible::verilog::analysis::checkers::forbid-negative-array-dim
  verible::verilog::analysis::checkers::forbidden-anonymous-enums-rule
  verible::verilog::analysis::checkers::forbidden-anonymous-structs-unions-rule
  verible::verilog::analysis::checkers::forbidden-macro-rule
  verible::verilog::analysis::checkers::forbidden-symbol-rule
  verible::verilog::analysis::checkers::generate-label-prefix-rule
  verible::verilog::analysis::checkers::generate-label-rule
  verible::verilog::analysis::checkers::instance-shadow-rule
  verible::verilog::analysis::checkers::interface-name-style-rule
  verible::verilog::analysis::checkers::legacy-generate-region-rule
  verible::verilog::analysis::checkers::legacy-genvar-declaration-rule
  verible::verilog::analysis::checkers::line-length-rule
  verible::verilog::analysis::checkers::macro-name-style-rule
  verible::verilog::analysis::checkers::macro-string-concatenation-rule
  verible::verilog::analysis::checkers::mismatched-labels-rule
  verible::verilog::analysis::checkers::module-begin-block-rule
  verible::verilog::analysis::checkers::module-filename-rule
  verible::verilog::analysis::checkers::module-instantiation-rules
  verible::verilog::analysis::checkers::no-tabs-rule
  verible::verilog::analysis::checkers::no-trailing-spaces-rule
  verible::verilog::analysis::checkers::numeric-format-string-style-rule
  verible::verilog::analysis::checkers::one-module-per-file-rule
  verible::verilog::analysis::checkers::package-filename-rule
  verible::verilog::analysis::checkers::packed-dimensions-rule
  verible::verilog::analysis::checkers::parameter-name-style-rule
  verible::verilog::analysis::checkers::parameter-type-name-style-rule
  verible::verilog::analysis::checkers::plusarg-assignment-rule
  verible::verilog::analysis::checkers::port-name-suffix-rule
  verible::verilog::analysis::checkers::positive-meaning-parameter-name-rule
  verible::verilog::analysis::checkers::posix-eof-rule
  verible::verilog::analysis::checkers::proper-parameter-declaration-rule
  verible::verilog::analysis::checkers::signal-name-style-rule
  verible::verilog::analysis::checkers::struct-union-name-style-rule
  verible::verilog::analysis::checkers::suggest-parentheses-rule
  verible::verilog::analysis::checkers::suspicious-semicolon-rule
  verible::verilog::analysis::checkers::truncated-numeric-literal-rule
  verible::verilog::analysis::checkers::undersized-binary-literal-rule
  verible::verilog::analysis::checkers::unpacked-dimensions-rule
  verible::verilog::analysis::checkers::uvm-macro-semicolon-rule
  verible::verilog::analysis::checkers::v2001-generate-begin-rule
  verible::verilog::analysis::checkers::void-cast-rule
)

add_library(banned-declared-name-patterns-rule STATIC banned-declared-name-patterns-rule.cc)
add_library(verible::verilog::analysis::checkers::banned-declared-name-patterns-rule ALIAS banned-declared-name-patterns-rule)
target_include_directories(banned-declared-name-patterns-rule PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(banned-declared-name-patterns-rule PUBLIC
  verible::common::analysis::lint-rule-status
  verible::common::analysis::syntax-tree-lint-rule
  verible::common::text::concrete-syntax-tree
  verible::common::text::symbol
  verible::common::text::syntax-tree-context
  verible::common::text::token-info
  verible::verilog::CST::module
  verible::verilog::CST::package
  verible::verilog::CST::verilog-matchers
  verible::verilog::CST::verilog-nonterminals
  verible::verilog::analysis::descriptions
  verible::verilog::analysis::lint-rule-registry
)

add_library(no-tabs-rule STATIC no-tabs-rule.cc)
add_library(verible::verilog::analysis::checkers::no-tabs-rule ALIAS no-tabs-rule)
target_include_directories(no-tabs-rule PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(no-tabs-rule PUBLIC
  verible::common::analysis::line-lint-rule
  verible::common::analysis::lint-rule-status
  verible::common::text::token-info
  verible::verilog::analysis::descriptions
  verible::verilog::analysis::lint-rule-registry
  verible::verilog::parser::verilog-token-enum
)

add_library(no-trailing-spaces-rule STATIC no-trailing-spaces-rule.cc)
add_library(verible::verilog::analysis::checkers::no-trailing-spaces-rule ALIAS no-trailing-spaces-rule)
target_include_directories(no-trailing-spaces-rule PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(no-trailing-spaces-rule PUBLIC
  verible::common::analysis::line-lint-rule
  verible::common::analysis::lint-rule-status
  verible::common::text::token-info
  verible::verilog::analysis::descriptions
  verible::verilog::analysis::lint-rule-registry
  verible::verilog::parser::verilog-token-enum
)

add_library(positive-meaning-parameter-name-rule STATIC positive-meaning-parameter-name-rule.cc)
add_library(verible::verilog::analysis::checkers::positive-meaning-parameter-name-rule ALIAS positive-meaning-parameter-name-rule)
target_include_directories(positive-meaning-parameter-name-rule PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(positive-meaning-parameter-name-rule PUBLIC
  verible::common::analysis::lint-rule-status
  verible::common::analysis::syntax-tree-lint-rule
  verible::common::analysis::matcher::bound-symbol-manager
  verible::common::text::symbol
  verible::common::text::syntax-tree-context
  verible::common::text::token-info
  verible::verilog::CST::parameters
  verible::verilog::CST::verilog-matchers
  verible::verilog::analysis::descriptions
  verible::verilog::analysis::lint-rule-registry
)

add_library(posix-eof-rule STATIC posix-eof-rule.cc)
add_library(verible::verilog::analysis::checkers::posix-eof-rule ALIAS posix-eof-rule)
target_include_directories(posix-eof-rule PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(posix-eof-rule PUBLIC
  verible::common::analysis::lint-rule-status
  verible::common::analysis::text-structure-lint-rule
  verible::common::text::text-structure
  verible::common::text::token-info
  verible::verilog::analysis::descriptions
  verible::verilog::analysis::lint-rule-registry
  verible::verilog::parser::verilog-token-enum
)

add_library(line-length-rule STATIC line-length-rule.cc)
add_library(verible::verilog::analysis::checkers::line-length-rule ALIAS line-length-rule)
target_include_directories(line-length-rule PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(line-length-rule PUBLIC
  verible::common::analysis::lint-rule-status
  verible::common::analysis::text-structure-lint-rule
  verible::common::strings::comment-utils
  verible::common::strings::utf8
  verible::common::text::config-utils
  verible::common::text::constants
  verible::common::text::text-structure
  verible::common::text::token-info
  verible::common::text::token-stream-view
  verible::common::util::iterator-range
  verible::verilog::analysis::descriptions
  verible::verilog::analysis::lint-rule-registry
  verible::verilog::analysis::verilog-linter-constants
  verible::verilog::parser::verilog-token-classifications
  verible::verilog::parser::verilog-token-enum
)

add_library(forbid-consecutive-null-statements-rule STATIC forbid-consecutive-null-statements-rule.cc)
add_library(verible::verilog::analysis::checkers::forbid-consecutive-null-statements-rule ALIAS forbid-consecutive-null-statements-rule)
target_include_directories(forbid-consecutive-null-statements-rule PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(forbid-consecutive-null-statements-rule PUBLIC
  verible::common::analysis::lint-rule-status
  verible::common::analysis::syntax-tree-lint-rule
  verible::common::text::concrete-syntax-leaf
  verible::common::text::symbol
  verible::common::text::syntax-tree-context
  verible::verilog::CST::verilog-matchers
  # fixdeps:: keep
  verible::verilog::CST::verilog-nonterminals
  verible::verilog::analysis::descriptions
  verible::verilog::analysis::lint-rule-registry
)

add_library(forbid-defparam-rule STATIC forbid-defparam-rule.cc)
add_library(verible::verilog::analysis::checkers::forbid-defparam-rule ALIAS forbid-defparam-rule)
target_include_directories(forbid-defparam-rule PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(forbid-defparam-rule PUBLIC
  verible::common::analysis::lint-rule-status
  verible::common::analysis::syntax-tree-lint-rule
  verible::common::analysis::matcher::bound-symbol-manager
  verible::common::text::concrete-syntax-leaf
  verible::common::text::symbol
  verible::common::text::syntax-tree-context
  verible::common::text::tree-utils
  verible::common::util::logging
  verible::verilog::CST::verilog-matchers
  # fixdeps:: keep
  verible::verilog::CST::verilog-nonterminals
  verible::verilog::analysis::descriptions
  verible::verilog::analysis::lint-rule-registry
  verible::verilog::parser::verilog-token-enum
)

add_library(mismatched-labels-rule STATIC mismatched-labels-rule.cc)
add_library(verible::verilog::analysis::checkers::mismatched-labels-rule ALIAS mismatched-labels-rule)
target_include_directories(mismatched-labels-rule PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(mismatched-labels-rule PUBLIC
  verible::common::analysis::lint-rule-status
  verible::common::analysis::syntax-tree-lint-rule
  verible::common::analysis::matcher::bound-symbol-manager
  verible::common::text::concrete-syntax-tree
  verible::common::text::symbol
  verible::common::text::syntax-tree-context
  verible::verilog::CST::seq-block
  verible::verilog::CST::verilog-matchers
  # fixdeps:: keep
  verible::verilog::analysis::descriptions
  verible::verilog::analysis::lint-rule-registry
)

add_library(module-begin-block-rule STATIC module-begin-block-rule.cc)
add_library(verible::verilog::analysis::checkers::module-begin-block-rule ALIAS module-begin-block-rule)
target_include_directories(module-begin-block-rule PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(module-begin-block-rule PUBLIC
  verible::common::analysis::lint-rule-status
  verible::common::analysis::syntax-tree-lint-rule
  verible::common::analysis::matcher::bound-symbol-manager
  verible::common::text::symbol
  verible::common::text::syntax-tree-context
  verible::verilog::CST::verilog-matchers
  # fixdeps:: keep
  verible::verilog::analysis::descriptions
  verible::verilog::analysis::lint-rule-registry
)

add_library(module-filename-rule STATIC module-filename-rule.cc)
add_library(verible::verilog::analysis::checkers::module-filename-rule ALIAS module-filename-rule)
target_include_directories(module-filename-rule PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(module-filename-rule PUBLIC
  verible::common::analysis::lint-rule-status
  verible::common::analysis::syntax-tree-search
  verible::common::analysis::text-structure-lint-rule
  verible::common::text::concrete-syntax-leaf
  verible::common::text::config-utils
  verible::common::text::symbol
  verible::common::text::text-structure
  verible::common::text::token-info
  verible::common::util::file-util
  verible::common::util::logging
  verible::verilog::CST::module
  verible::verilog::CST::verilog-nonterminals
  verible::verilog::analysis::descriptions
  verible::verilog::analysis::lint-rule-registry
)

add_library(package-filename-rule STATIC package-filename-rule.cc)
add_library(verible::verilog::analysis::checkers::package-filename-rule ALIAS package-filename-rule)
target_include_directories(package-filename-rule PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(package-filename-rule PUBLIC
  verible::common::analysis::lint-rule-status
  verible::common::analysis::syntax-tree-search
  verible::common::analysis::text-structure-lint-rule
  verible::common::text::config-utils
  verible::common::text::text-structure
  verible::common::text::token-info
  verible::common::util::file-util
  verible::verilog::CST::package
  verible::verilog::analysis::descriptions
  verible::verilog::analysis::lint-rule-registry
)

add_library(module-instantiation-rules STATIC module-instantiation-rules.cc)
add_library(verible::verilog::analysis::checkers::module-instantiation-rules ALIAS module-instantiation-rules)
target_include_directories(module-instantiation-rules PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(module-instantiation-rules PUBLIC
  verible::common::analysis::lint-rule-status
  verible::common::analysis::syntax-tree-lint-rule
  verible::common::analysis::matcher::bound-symbol-manager
  verible::common::text::concrete-syntax-leaf
  verible::common::text::concrete-syntax-tree
  verible::common::text::symbol
  verible::common::text::syntax-tree-context
  verible::common::text::token-info
  verible::common::text::tree-utils
  verible::common::util::casts
  verible::common::util::logging
  verible::verilog::CST::context-functions
  verible::verilog::CST::verilog-matchers
  verible::verilog::CST::verilog-nonterminals
  verible::verilog::analysis::descriptions
  verible::verilog::analysis::lint-rule-registry
)

add_library(one-module-per-file-rule STATIC one-module-per-file-rule.cc)
add_library(verible::verilog::analysis::checkers::one-module-per-file-rule ALIAS one-module-per-file-rule)
target_include_directories(one-module-per-file-rule PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(one-module-per-file-rule PUBLIC
  verible::common::analysis::lint-rule-status
  verible::common::analysis::syntax-tree-search
  verible::common::analysis::text-structure-lint-rule
  verible::common::text::text-structure
  verible::common::util::logging
  verible::verilog::CST::module
  verible::verilog::CST::verilog-nonterminals
  verible::verilog::analysis::descriptions
  verible::verilog::analysis::lint-rule-registry
)

add_library(endif-comment-rule STATIC endif-comment-rule.cc)
add_library(verible::verilog::analysis::checkers::endif-comment-rule ALIAS endif-comment-rule)
target_include_directories(endif-comment-rule PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(endif-comment-rule PUBLIC
  verible::common::analysis::lint-rule-status
  verible::common::analysis::token-stream-lint-rule
  verible::common::strings::comment-utils
  verible::common::text::token-info
  verible::verilog::analysis::descriptions
  verible::verilog::analysis::lint-rule-registry
  verible::verilog::parser::verilog-token-enum
)

add_library(forbidden-anonymous-enums-rule STATIC forbidden-anonymous-enums-rule.cc)
add_library(verible::verilog::analysis::checkers::forbidden-anonymous-enums-rule ALIAS forbidden-anonymous-enums-rule)
target_include_directories(forbidden-anonymous-enums-rule PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(forbidden-anonymous-enums-rule PUBLIC
  verible::common::analysis::lint-rule-status
  verible::common::analysis::syntax-tree-lint-rule
  verible::common::analysis::matcher::bound-symbol-manager
  verible::common::text::symbol
  verible::common::text::syntax-tree-context
  verible::verilog::CST::verilog-matchers
  verible::verilog::CST::verilog-nonterminals
  verible::verilog::analysis::descriptions
  verible::verilog::analysis::lint-rule-registry
)

add_library(enum-name-style-rule STATIC enum-name-style-rule.cc)
add_library(verible::verilog::analysis::checkers::enum-name-style-rule ALIAS enum-name-style-rule)
target_include_directories(enum-name-style-rule PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(enum-name-style-rule PUBLIC
  verible::common::analysis::lint-rule-status
  verible::common::analysis::syntax-tree-lint-rule
  verible::common::analysis::matcher::bound-symbol-manager
  verible::common::text::config-utils
  verible::common::text::symbol
  verible::common::text::syntax-tree-context
  verible::common::util::logging
  verible::verilog::CST::type
  verible::verilog::CST::verilog-matchers
  verible::verilog::analysis::descriptions
  verible::verilog::analysis::lint-rule-registry
)

add_library(forbidden-macro-rule STATIC forbidden-macro-rule.cc)
add_library(verible::verilog::analysis::checkers::forbidden-macro-rule ALIAS forbidden-macro-rule)
target_include_directories(forbidden-macro-rule PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(forbidden-macro-rule PUBLIC
  verible::common::analysis::citation
  verible::common::analysis::lint-rule-status
  verible::common::analysis::syntax-tree-lint-rule
  verible::common::analysis::matcher::bound-symbol-manager
  verible::common::text::concrete-syntax-leaf
  verible::common::text::symbol
  verible::common::text::syntax-tree-context
  verible::common::text::token-info
  verible::common::util::container-util
  verible::verilog::CST::verilog-matchers
  verible::verilog::analysis::descriptions
  verible::verilog::analysis::lint-rule-registry
)

add_library(forbidden-anonymous-structs-unions-rule STATIC forbidden-anonymous-structs-unions-rule.cc)
add_library(verible::verilog::analysis::checkers::forbidden-anonymous-structs-unions-rule ALIAS forbidden-anonymous-structs-unions-rule)
target_include_directories(forbidden-anonymous-structs-unions-rule PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(forbidden-anonymous-structs-unions-rule PUBLIC
  verible::common::analysis::lint-rule-status
  verible::common::analysis::syntax-tree-lint-rule
  verible::common::analysis::matcher::bound-symbol-manager
  verible::common::text::config-utils
  verible::common::text::symbol
  verible::common::text::syntax-tree-context
  verible::verilog::CST::verilog-matchers
  verible::verilog::CST::verilog-nonterminals
  verible::verilog::analysis::descriptions
  verible::verilog::analysis::lint-rule-registry
)

add_library(forbidden-symbol-rule STATIC forbidden-symbol-rule.cc)
add_library(verible::verilog::analysis::checkers::forbidden-symbol-rule ALIAS forbidden-symbol-rule)
target_include_directories(forbidden-symbol-rule PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(forbidden-symbol-rule PUBLIC
  verible::common::analysis::lint-rule-status
  verible::common::analysis::syntax-tree-lint-rule
  verible::common::analysis::matcher::bound-symbol-manager
  verible::common::text::concrete-syntax-leaf
  verible::common::text::symbol
  verible::common::text::syntax-tree-context
  verible::common::text::token-info
  verible::common::util::container-util
  verible::verilog::CST::verilog-matchers
  verible::verilog::analysis::descriptions
  verible::verilog::analysis::lint-rule-registry
)

add_library(generate-label-rule STATIC generate-label-rule.cc)
add_library(verible::verilog::analysis::checkers::generate-label-rule ALIAS generate-label-rule)
target_include_directories(generate-label-rule PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(generate-label-rule PUBLIC
  verible::common::analysis::lint-rule-status
  verible::common::analysis::syntax-tree-lint-rule
  verible::common::analysis::matcher::bound-symbol-manager
  verible::common::analysis::matcher::core-matchers
  verible::common::text::symbol
  verible::common::text::syntax-tree-context
  verible::verilog::CST::verilog-matchers
  verible::verilog::analysis::descriptions
  verible::verilog::analysis::lint-rule-registry
)

add_library(generate-label-prefix-rule STATIC generate-label-prefix-rule.cc)
add_library(verible::verilog::analysis::checkers::generate-label-prefix-rule ALIAS generate-label-prefix-rule)
target_include_directories(generate-label-prefix-rule PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(generate-label-prefix-rule PUBLIC
  verible::common::analysis::lint-rule-status
  verible::common::analysis::syntax-tree-lint-rule
  verible::common::analysis::matcher::bound-symbol-manager
  verible::common::text::symbol
  verible::common::text::syntax-tree-context
  verible::common::text::token-info
  verible::common::text::tree-utils
  verible::verilog::CST::seq-block
  verible::verilog::CST::verilog-matchers
  verible::verilog::CST::verilog-nonterminals
  verible::verilog::analysis::descriptions
  verible::verilog::analysis::lint-rule-registry
)

add_library(v2001-generate-begin-rule STATIC v2001-generate-begin-rule.cc)
add_library(verible::verilog::analysis::checkers::v2001-generate-begin-rule ALIAS v2001-generate-begin-rule)
target_include_directories(v2001-generate-begin-rule PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(v2001-generate-begin-rule PUBLIC
  verible::common::analysis::lint-rule-status
  verible::common::analysis::syntax-tree-lint-rule
  verible::common::analysis::matcher::bound-symbol-manager
  verible::common::text::concrete-syntax-leaf
  verible::common::text::concrete-syntax-tree
  verible::common::text::symbol
  verible::common::text::syntax-tree-context
  verible::common::text::tree-utils
  verible::verilog::CST::verilog-matchers
  verible::verilog::analysis::descriptions
  verible::verilog::analysis::lint-rule-registry
)

add_library(void-cast-rule STATIC void-cast-rule.cc)
add_library(verible::verilog::analysis::checkers::void-cast-rule ALIAS void-cast-rule)
target_include_directories(void-cast-rule PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(void-cast-rule PUBLIC
  verible::common::analysis::lint-rule-status
  verible::common::analysis::syntax-tree-lint-rule
  verible::common::analysis::matcher::bound-symbol-manager
  verible::common::analysis::matcher::core-matchers
  verible::common::text::concrete-syntax-leaf
  verible::common::text::concrete-syntax-tree
  verible::common::text::symbol
  verible::common::text::syntax-tree-context
  verible::common::text::token-info
  verible::common::text::tree-utils
  verible::common::util::logging
  verible::verilog::CST::verilog-matchers
  verible::verilog::analysis::descriptions
  verible::verilog::analysis::lint-rule-registry
)

add_library(undersized-binary-literal-rule STATIC undersized-binary-literal-rule.cc)
add_library(verible::verilog::analysis::checkers::undersized-binary-literal-rule ALIAS undersized-binary-literal-rule)
target_include_directories(undersized-binary-literal-rule PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(undersized-binary-literal-rule PUBLIC
  verible::common::analysis::lint-rule-status
  verible::common::analysis::syntax-tree-lint-rule
  verible::common::analysis::matcher::bound-symbol-manager
  verible::common::text::concrete-syntax-leaf
  verible::common::text::concrete-syntax-tree
  verible::common::text::config-utils
  verible::common::text::symbol
  verible::common::text::syntax-tree-context
  verible::common::text::token-info
  verible::common::util::logging
  verible::verilog::CST::numbers
  verible::verilog::CST::verilog-matchers
  verible::verilog::analysis::descriptions
  verible::verilog::analysis::lint-rule-registry
)

add_library(truncated-numeric-literal-rule STATIC truncated-numeric-literal-rule.cc)
add_library(verible::verilog::analysis::checkers::truncated-numeric-literal-rule ALIAS truncated-numeric-literal-rule)
target_include_directories(truncated-numeric-literal-rule PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(truncated-numeric-literal-rule PUBLIC
  verible::common::analysis::lint-rule-status
  verible::common::analysis::syntax-tree-lint-rule
  verible::common::analysis::matcher::bound-symbol-manager
  verible::common::text::concrete-syntax-leaf
  verible::common::text::concrete-syntax-tree
  verible::common::text::symbol
  verible::common::text::syntax-tree-context
  verible::common::text::token-info
  verible::verilog::CST::numbers
  verible::verilog::CST::verilog-matchers
  verible::verilog::analysis::descriptions
  verible::verilog::analysis::lint-rule-registry
  absl::int128
)

add_library(create-object-name-match-rule STATIC create-object-name-match-rule.cc)
add_library(verible::verilog::analysis::checkers::create-object-name-match-rule ALIAS create-object-name-match-rule)
target_include_directories(create-object-name-match-rule PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(create-object-name-match-rule PUBLIC
  verible::common::analysis::lint-rule-status
  verible::common::analysis::syntax-tree-lint-rule
  verible::common::analysis::matcher::bound-symbol-manager
  verible::common::text::concrete-syntax-leaf
  verible::common::text::concrete-syntax-tree
  verible::common::text::symbol
  verible::common::text::syntax-tree-context
  verible::common::text::token-info
  verible::common::util::casts
  verible::verilog::CST::expression
  verible::verilog::CST::verilog-matchers
  verible::verilog::CST::verilog-nonterminals
  verible::verilog::analysis::descriptions
  verible::verilog::analysis::lint-rule-registry
  verible::verilog::parser::verilog-token-enum
)

add_library(always-comb-rule STATIC always-comb-rule.cc)
add_library(verible::verilog::analysis::checkers::always-comb-rule ALIAS always-comb-rule)
target_include_directories(always-comb-rule PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(always-comb-rule PUBLIC
  verible::common::analysis::lint-rule-status
  verible::common::analysis::syntax-tree-lint-rule
  verible::common::analysis::matcher::bound-symbol-manager
  verible::common::text::concrete-syntax-leaf
  verible::common::text::concrete-syntax-tree
  verible::common::text::symbol
  verible::common::text::syntax-tree-context
  verible::common::text::tree-utils
  verible::verilog::CST::statement
  verible::verilog::CST::verilog-matchers
  verible::verilog::analysis::descriptions
  verible::verilog::analysis::lint-rule-registry
)

add_library(forbid-line-continuations-rule STATIC forbid-line-continuations-rule.cc)
add_library(verible::verilog::analysis::checkers::forbid-line-continuations-rule ALIAS forbid-line-continuations-rule)
target_include_directories(forbid-line-continuations-rule PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(forbid-line-continuations-rule PUBLIC
  verible::common::analysis::lint-rule-status
  verible::common::analysis::syntax-tree-lint-rule
  verible::common::analysis::matcher::bound-symbol-manager
  verible::common::text::symbol
  verible::common::text::syntax-tree-context
  verible::common::text::tree-utils
  verible::verilog::CST::verilog-matchers
  verible::verilog::analysis::descriptions
  verible::verilog::analysis::lint-rule-registry
  verible::verilog::parser::verilog-token-enum
)

add_library(suggest-parentheses-rule STATIC suggest-parentheses-rule.cc)
add_library(verible::verilog::analysis::checkers::suggest-parentheses-rule ALIAS suggest-parentheses-rule)
target_include_directories(suggest-parentheses-rule PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(suggest-parentheses-rule PUBLIC
  verible::common::analysis::lint-rule-status
  verible::common::analysis::syntax-tree-lint-rule
  verible::common::text::concrete-syntax-tree
  verible::common::text::symbol
  verible::common::text::syntax-tree-context
  verible::common::text::token-info
  verible::common::text::tree-utils
  verible::verilog::CST::expression
  verible::verilog::CST::verilog-nonterminals
  verible::verilog::analysis::descriptions
  verible::verilog::analysis::lint-rule-registry
  verible::verilog::parser::verilog-token-enum
)

add_library(always-comb-blocking-rule STATIC always-comb-blocking-rule.cc)
add_library(verible::verilog::analysis::checkers::always-comb-blocking-rule ALIAS always-comb-blocking-rule)
target_include_directories(always-comb-blocking-rule PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(always-comb-blocking-rule PUBLIC
  verible::common::analysis::lint-rule-status
  verible::common::analysis::syntax-tree-lint-rule
  verible::common::analysis::syntax-tree-search
  verible::common::analysis::matcher::bound-symbol-manager
  verible::common::text::concrete-syntax-leaf
  verible::common::text::concrete-syntax-tree
  verible::common::text::symbol
  verible::common::text::syntax-tree-context
  verible::common::text::tree-utils
  verible::common::util::casts
  verible::verilog::CST::verilog-matchers
  verible::verilog::CST::verilog-nonterminals
  verible::verilog::analysis::descriptions
  verible::verilog::analysis::lint-rule-registry
  verible::verilog::parser::verilog-token-enum
)

add_library(always-ff-non-blocking-rule STATIC always-ff-non-blocking-rule.cc)
add_library(verible::verilog::analysis::checkers::always-ff-non-blocking-rule ALIAS always-ff-non-blocking-rule)
target_include_directories(always-ff-non-blocking-rule PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(always-ff-non-blocking-rule PUBLIC
  verible::common::analysis::lint-rule-status
  verible::common::analysis::syntax-tree-lint-rule
  verible::common::analysis::syntax-tree-search
  verible::common::analysis::matcher::bound-symbol-manager
  verible::common::text::concrete-syntax-leaf
  verible::common::text::concrete-syntax-tree
  verible::common::text::config-utils
  verible::common::text::symbol
  verible::common::text::syntax-tree-context
  verible::common::util::casts
  verible::common::util::logging
  verible::verilog::CST::verilog-matchers
  verible::verilog::CST::verilog-nonterminals
  verible::verilog::analysis::descriptions
  verible::verilog::analysis::lint-rule-registry
)

add_library(explicit-begin-rule STATIC explicit-begin-rule.cc)
add_library(verible::verilog::analysis::checkers::explicit-begin-rule ALIAS explicit-begin-rule)
target_include_directories(explicit-begin-rule PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(explicit-begin-rule PUBLIC
  verible::common::analysis::lint-rule-status
  verible::common::analysis::token-stream-lint-rule
  verible::common::text::config-utils
  verible::common::text::token-info
  verible::verilog::analysis::descriptions
  verible::verilog::analysis::lint-rule-registry
  verible::verilog::parser::verilog-token-enum
  absl::core_headers
)

add_library(explicit-function-lifetime-rule STATIC explicit-function-lifetime-rule.cc)
add_library(verible::verilog::analysis::checkers::explicit-function-lifetime-rule ALIAS explicit-function-lifetime-rule)
target_include_directories(explicit-function-lifetime-rule PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(explicit-function-lifetime-rule PUBLIC
  verible::common::analysis::lint-rule-status
  verible::common::analysis::syntax-tree-lint-rule
  verible::common::analysis::matcher::bound-symbol-manager
  verible::common::text::symbol
  verible::common::text::syntax-tree-context
  verible::common::text::token-info
  verible::common::text::tree-utils
  verible::common::util::logging
  verible::verilog::CST::context-functions
  verible::verilog::CST::functions
  verible::verilog::CST::identifier
  verible::verilog::CST::verilog-matchers
  verible::verilog::analysis::descriptions
  verible::verilog::analysis::lint-rule-registry
  verible::verilog::parser::verilog-token-enum
)

add_library(explicit-task-lifetime-rule STATIC explicit-task-lifetime-rule.cc)
add_library(verible::verilog::analysis::checkers::explicit-task-lifetime-rule ALIAS explicit-task-lifetime-rule)
target_include_directories(explicit-task-lifetime-rule PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(explicit-task-lifetime-rule PUBLIC
  verible::common::analysis::lint-rule-status
  verible::common::analysis::syntax-tree-lint-rule
  verible::common::analysis::matcher::bound-symbol-manager
  verible::common::text::symbol
  verible::common::text::syntax-tree-context
  verible::common::text::token-info
  verible::common::text::tree-utils
  verible::verilog::CST::context-functions
  verible::verilog::CST::identifier
  verible::verilog::CST::tasks
  verible::verilog::CST::verilog-matchers
  verible::verilog::analysis::descriptions
  verible::verilog::analysis::lint-rule-registry
  verible::verilog::parser::verilog-token-enum
)

add_library(packed-dimensions-rule STATIC packed-dimensions-rule.cc)
add_library(verible::verilog::analysis::checkers::packed-dimensions-rule ALIAS packed-dimensions-rule)
target_include_directories(packed-dimensions-rule PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(packed-dimensions-rule PUBLIC
  verible::common::analysis::lint-rule-status
  verible::common::analysis::syntax-tree-lint-rule
  verible::common::analysis::matcher::bound-symbol-manager
  verible::common::text::symbol
  verible::common::text::syntax-tree-context
  verible::common::text::token-info
  verible::common::text::tree-utils
  verible::common::util::logging
  verible::verilog::CST::context-functions
  verible::verilog::CST::dimensions
  verible::verilog::CST::expression
  verible::verilog::CST::verilog-matchers
  verible::verilog::analysis::descriptions
  verible::verilog::analysis::lint-rule-registry
  verible::verilog::parser::verilog-token-enum
)

add_library(unpacked-dimensions-rule STATIC unpacked-dimensions-rule.cc)
add_library(verible::verilog::analysis::checkers::unpacked-dimensions-rule ALIAS unpacked-dimensions-rule)
target_include_directories(unpacked-dimensions-rule PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(unpacked-dimensions-rule PUBLIC
  verible::common::analysis::lint-rule-status
  verible::common::analysis::syntax-tree-lint-rule
  verible::common::analysis::matcher::bound-symbol-manager
  verible::common::text::symbol
  verible::common::text::syntax-tree-context
  verible::common::text::token-info
  verible::common::text::tree-utils
  verible::common::util::logging
  verible::verilog::CST::context-functions
  verible::verilog::CST::dimensions
  verible::verilog::CST::expression
  verible::verilog::CST::verilog-matchers
  verible::verilog::CST::verilog-nonterminals
  verible::verilog::analysis::descriptions
  verible::verilog::analysis::lint-rule-registry
  verible::verilog::parser::verilog-token-enum
)

add_library(forbid-negative-array-dim STATIC forbid-negative-array-dim.cc)
add_library(verible::verilog::analysis::checkers::forbid-negative-array-dim ALIAS forbid-negative-array-dim)
target_include_directories(forbid-negative-array-dim PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(forbid-negative-array-dim PUBLIC
  verible::common::analysis::lint-rule-status
  verible::common::analysis::syntax-tree-lint-rule
  verible::common::analysis::matcher::bound-symbol-manager
  verible::common::text::symbol
  verible::common::text::syntax-tree-context
  verible::common::text::token-info
  verible::common::text::tree-utils
  verible::verilog::CST::expression
  verible::verilog::CST::verilog-matchers
  verible::verilog::CST::verilog-nonterminals
  verible::verilog::analysis::descriptions
  verible::verilog::analysis::lint-rule-registry
  verible::verilog::parser::verilog-token-enum
)

add_library(case-missing-default-rule STATIC case-missing-default-rule.cc)
add_library(verible::verilog::analysis::checkers::case-missing-default-rule ALIAS case-missing-default-rule)
target_include_directories(case-missing-default-rule PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(case-missing-default-rule PUBLIC
  verible::common::analysis::lint-rule-status
  verible::common::analysis::syntax-tree-lint-rule
  verible::common::analysis::matcher::bound-symbol-manager
  verible::common::analysis::matcher::matcher-builders
  verible::common::text::concrete-syntax-tree
  verible::common::text::symbol
  verible::common::text::syntax-tree-context
  verible::common::text::tree-utils
  verible::verilog::CST::verilog-matchers
  verible::verilog::CST::verilog-nonterminals
  verible::verilog::analysis::descriptions
  verible::verilog::analysis::lint-rule-registry
)

add_library(constraint-name-style-rule STATIC constraint-name-style-rule.cc)
add_library(verible::verilog::analysis::checkers::constraint-name-style-rule ALIAS constraint-name-style-rule)
target_include_directories(constraint-name-style-rule PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(constraint-name-style-rule PUBLIC
  verible::common::analysis::lint-rule-status
  verible::common::analysis::syntax-tree-lint-rule
  verible::common::analysis::matcher::bound-symbol-manager
  verible::common::text::config-utils
  verible::common::text::symbol
  verible::common::text::syntax-tree-context
  verible::common::text::token-info
  verible::verilog::CST::constraints
  verible::verilog::CST::verilog-matchers
  verible::verilog::analysis::descriptions
  verible::verilog::analysis::lint-rule-registry
)

add_library(disable-statement-rule STATIC disable-statement-rule.cc)
add_library(verible::verilog::analysis::checkers::disable-statement-rule ALIAS disable-statement-rule)
target_include_directories(disable-statement-rule PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(disable-statement-rule PUBLIC
  verible::common::analysis::lint-rule-status
  verible::common::analysis::syntax-tree-lint-rule
  verible::common::analysis::matcher::bound-symbol-manager
  verible::common::text::symbol
  verible::common::text::syntax-tree-context
  verible::common::text::tree-utils
  verible::common::util::iterator-adaptors
  verible::verilog::CST::identifier
  verible::verilog::CST::verilog-matchers
  verible::verilog::CST::verilog-nonterminals
  verible::verilog::analysis::descriptions
  verible::verilog::analysis::lint-rule-registry
)

add_library(macro-name-style-rule STATIC macro-name-style-rule.cc)
add_library(verible::verilog::analysis::checkers::macro-name-style-rule ALIAS macro-name-style-rule)
target_include_directories(macro-name-style-rule PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(macro-name-style-rule PUBLIC
  verible::common::analysis::lint-rule-status
  verible::common::analysis::token-stream-lint-rule
  verible::common::text::config-utils
  verible::common::text::token-info
  verible::verilog::analysis::descriptions
  verible::verilog::analysis::lint-rule-registry
  verible::verilog::parser::verilog-lexer
  verible::verilog::parser::verilog-token-classifications
  verible::verilog::parser::verilog-token-enum
)

add_library(macro-string-concatenation-rule STATIC macro-string-concatenation-rule.cc)
add_library(verible::verilog::analysis::checkers::macro-string-concatenation-rule ALIAS macro-string-concatenation-rule)
target_include_directories(macro-string-concatenation-rule PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(macro-string-concatenation-rule PUBLIC
  verible::common::analysis::lint-rule-status
  verible::common::analysis::token-stream-lint-rule
  verible::common::text::token-info
  verible::common::util::value-saver
  verible::verilog::analysis::descriptions
  verible::verilog::analysis::lint-rule-registry
  verible::verilog::parser::verilog-lexer
  verible::verilog::parser::verilog-token-classifications
  verible::verilog::parser::verilog-token-enum
)

add_library(numeric-format-string-style-rule STATIC numeric-format-string-style-rule.cc)
add_library(verible::verilog::analysis::checkers::numeric-format-string-style-rule ALIAS numeric-format-string-style-rule)
target_include_directories(numeric-format-string-style-rule PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(numeric-format-string-style-rule PUBLIC
  verible::common::analysis::lint-rule-status
  verible::common::analysis::token-stream-lint-rule
  verible::common::text::token-info
  verible::verilog::analysis::descriptions
  verible::verilog::analysis::lint-rule-registry
  verible::verilog::parser::verilog-lexer
  verible::verilog::parser::verilog-token-classifications
  verible::verilog::parser::verilog-token-enum
)

add_library(parameter-name-style-rule STATIC parameter-name-style-rule.cc)
add_library(verible::verilog::analysis::checkers::parameter-name-style-rule ALIAS parameter-name-style-rule)
target_include_directories(parameter-name-style-rule PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(parameter-name-style-rule PUBLIC
  verible::common::analysis::lint-rule-status
  verible::common::analysis::syntax-tree-lint-rule
  verible::common::analysis::matcher::bound-symbol-manager
  verible::common::text::config-utils
  verible::common::text::symbol
  verible::common::text::syntax-tree-context
  verible::common::text::token-info
  verible::verilog::CST::parameters
  verible::verilog::CST::verilog-matchers
  verible::verilog::analysis::descriptions
  verible::verilog::analysis::lint-rule-registry
  verible::verilog::parser::verilog-token-enum
)

add_library(parameter-type-name-style-rule STATIC parameter-type-name-style-rule.cc)
add_library(verible::verilog::analysis::checkers::parameter-type-name-style-rule ALIAS parameter-type-name-style-rule)
target_include_directories(parameter-type-name-style-rule PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(parameter-type-name-style-rule PUBLIC
  verible::common::analysis::lint-rule-status
  verible::common::analysis::syntax-tree-lint-rule
  verible::common::analysis::matcher::bound-symbol-manager
  verible::common::strings::naming-utils
  verible::common::text::symbol
  verible::common::text::syntax-tree-context
  verible::common::text::token-info
  verible::verilog::CST::parameters
  verible::verilog::CST::verilog-matchers
  verible::verilog::analysis::descriptions
  verible::verilog::analysis::lint-rule-registry
)

add_library(proper-parameter-declaration-rule STATIC proper-parameter-declaration-rule.cc)
add_library(verible::verilog::analysis::checkers::proper-parameter-declaration-rule ALIAS proper-parameter-declaration-rule)
target_include_directories(proper-parameter-declaration-rule PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(proper-parameter-declaration-rule PUBLIC
  verible::common::analysis::lint-rule-status
  verible::common::analysis::syntax-tree-lint-rule
  verible::common::analysis::matcher::bound-symbol-manager
  verible::common::text::config-utils
  verible::common::text::symbol
  verible::common::text::syntax-tree-context
  verible::common::text::token-info
  verible::verilog::CST::context-functions
  verible::verilog::CST::parameters
  verible::verilog::CST::verilog-matchers
  verible::verilog::analysis::descriptions
  verible::verilog::analysis::lint-rule-registry
  verible::verilog::parser::verilog-token-enum
)

add_library(plusarg-assignment-rule STATIC plusarg-assignment-rule.cc)
add_library(verible::verilog::analysis::checkers::plusarg-assignment-rule ALIAS plusarg-assignment-rule)
target_include_directories(plusarg-assignment-rule PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(plusarg-assignment-rule PUBLIC
  verible::common::analysis::lint-rule-status
  verible::common::analysis::syntax-tree-lint-rule
  verible::common::analysis::matcher::bound-symbol-manager
  verible::common::text::concrete-syntax-leaf
  verible::common::text::symbol
  verible::common::text::syntax-tree-context
  verible::common::text::token-info
  verible::verilog::CST::verilog-matchers
  verible::verilog::analysis::descriptions
  verible::verilog::analysis::lint-rule-registry
)

add_library(port-name-suffix-rule STATIC port-name-suffix-rule.cc)
add_library(verible::verilog::analysis::checkers::port-name-suffix-rule ALIAS port-name-suffix-rule)
target_include_directories(port-name-suffix-rule PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(port-name-suffix-rule PUBLIC
  verible::common::analysis::lint-rule-status
  verible::common::analysis::syntax-tree-lint-rule
  verible::common::analysis::matcher::bound-symbol-manager
  verible::common::text::symbol
  verible::common::text::syntax-tree-context
  verible::common::text::token-info
  verible::common::util::logging
  verible::verilog::CST::port
  verible::verilog::CST::verilog-matchers
  verible::verilog::analysis::descriptions
  verible::verilog::analysis::lint-rule-registry
)

add_library(explicit-parameter-storage-type-rule STATIC explicit-parameter-storage-type-rule.cc)
add_library(verible::verilog::analysis::checkers::explicit-parameter-storage-type-rule ALIAS explicit-parameter-storage-type-rule)
target_include_directories(explicit-parameter-storage-type-rule PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(explicit-parameter-storage-type-rule PUBLIC
  verible::common::analysis::lint-rule-status
  verible::common::analysis::syntax-tree-lint-rule
  verible::common::analysis::matcher::bound-symbol-manager
  verible::common::text::config-utils
  verible::common::text::symbol
  verible::common::text::syntax-tree-context
  verible::common::text::token-info
  verible::common::text::tree-utils
  verible::common::util::logging
  verible::verilog::CST::parameters
  verible::verilog::CST::verilog-matchers
  # fixdeps:: keep
  verible::verilog::analysis::descriptions
  verible::verilog::analysis::lint-rule-registry
  verible::verilog::parser::verilog-token-enum
)

add_library(explicit-function-task-parameter-type-rule STATIC explicit-function-task-parameter-type-rule.cc)
add_library(verible::verilog::analysis::checkers::explicit-function-task-parameter-type-rule ALIAS explicit-function-task-parameter-type-rule)
target_include_directories(explicit-function-task-parameter-type-rule PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(explicit-function-task-parameter-type-rule PUBLIC
  verible::common::analysis::lint-rule-status
  verible::common::analysis::syntax-tree-lint-rule
  verible::common::analysis::matcher::bound-symbol-manager
  verible::common::text::symbol
  verible::common::text::syntax-tree-context
  verible::common::util::logging
  verible::verilog::CST::port
  verible::verilog::CST::type
  verible::verilog::CST::verilog-matchers
  verible::verilog::analysis::descriptions
  verible::verilog::analysis::lint-rule-registry
)

add_library(signal-name-style-rule STATIC signal-name-style-rule.cc)
add_library(verible::verilog::analysis::checkers::signal-name-style-rule ALIAS signal-name-style-rule)
target_include_directories(signal-name-style-rule PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(signal-name-style-rule PUBLIC
  verible::common::analysis::lint-rule-status
  verible::common::analysis::syntax-tree-lint-rule
  verible::common::analysis::matcher::bound-symbol-manager
  verible::common::text::concrete-syntax-leaf
  verible::common::text::config-utils
  verible::common::text::symbol
  verible::common::text::syntax-tree-context
  verible::common::text::token-info
  verible::common::util::logging
  verible::verilog::CST::data
  verible::verilog::CST::net
  verible::verilog::CST::port
  verible::verilog::CST::verilog-matchers
  verible::verilog::analysis::descriptions
  verible::verilog::analysis::lint-rule-registry
)

add_library(struct-union-name-style-rule STATIC struct-union-name-style-rule.cc)
add_library(verible::verilog::analysis::checkers::struct-union-name-style-rule ALIAS struct-union-name-style-rule)
target_include_directories(struct-union-name-style-rule PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(struct-union-name-style-rule PUBLIC
  verible::common::analysis::lint-rule-status
  verible::common::analysis::syntax-tree-lint-rule
  verible::common::analysis::matcher::bound-symbol-manager
  verible::common::text::config-utils
  verible::common::text::symbol
  verible::common::text::syntax-tree-context
  verible::common::util::logging
  verible::verilog::CST::type
  verible::verilog::CST::verilog-matchers
  verible::verilog::analysis::descriptions
  verible::verilog::analysis::lint-rule-registry
)

add_library(interface-name-style-rule STATIC interface-name-style-rule.cc)
add_library(verible::verilog::analysis::checkers::interface-name-style-rule ALIAS interface-name-style-rule)
target_include_directories(interface-name-style-rule PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(interface-name-style-rule PUBLIC
  verible::common::analysis::lint-rule-status
  verible::common::analysis::syntax-tree-lint-rule
  verible::common::analysis::matcher::bound-symbol-manager
  verible::common::text::config-utils
  verible::common::text::symbol
  verible::common::text::syntax-tree-context
  verible::common::text::token-info
  verible::verilog::CST::module
  verible::verilog::CST::type
  verible::verilog::CST::verilog-matchers
  verible::verilog::analysis::descriptions
  verible::verilog::analysis::lint-rule-registry
)

add_library(instance-shadow-rule STATIC instance-shadow-rule.cc)
add_library(verible::verilog::analysis::checkers::instance-shadow-rule ALIAS instance-shadow-rule)
target_include_directories(instance-shadow-rule PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(instance-shadow-rule PUBLIC
  verible::common::analysis::citation
  verible::common::analysis::lint-rule-status
  verible::common::analysis::syntax-tree-lint-rule
  verible::common::analysis::syntax-tree-search
  verible::common::analysis::matcher::bound-symbol-manager
  verible::common::text::symbol
  verible::common::text::syntax-tree-context
  verible::common::text::tree-utils
  verible::common::util::iterator-adaptors
  verible::verilog::CST::identifier
  verible::verilog::CST::verilog-matchers
  verible::verilog::CST::verilog-nonterminals
  verible::verilog::analysis::descriptions
  verible::verilog::analysis::lint-rule-registry
)

add_library(legacy-genvar-declaration-rule STATIC legacy-genvar-declaration-rule.cc)
add_library(verible::verilog::analysis::checkers::legacy-genvar-declaration-rule ALIAS legacy-genvar-declaration-rule)
target_include_directories(legacy-genvar-declaration-rule PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(legacy-genvar-declaration-rule PUBLIC
  verible::common::analysis::lint-rule-status
  verible::common::analysis::syntax-tree-lint-rule
  verible::common::text::concrete-syntax-tree
  verible::common::text::symbol
  verible::common::text::syntax-tree-context
  verible::common::text::tree-utils
  verible::verilog::CST::identifier
  verible::verilog::CST::verilog-nonterminals
  verible::verilog::analysis::descriptions
  verible::verilog::analysis::lint-rule-registry
)

add_library(legacy-generate-region-rule STATIC legacy-generate-region-rule.cc)
add_library(verible::verilog::analysis::checkers::legacy-generate-region-rule ALIAS legacy-generate-region-rule)
target_include_directories(legacy-generate-region-rule PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(legacy-generate-region-rule PUBLIC
  verible::common::analysis::lint-rule-status
  verible::common::analysis::syntax-tree-lint-rule
  verible::common::analysis::matcher::matcher-builders
  verible::common::text::concrete-syntax-tree
  verible::common::text::symbol
  verible::common::text::syntax-tree-context
  verible::common::text::tree-utils
  verible::common::util::logging
  verible::verilog::CST::verilog-nonterminals
  verible::verilog::analysis::descriptions
  verible::verilog::analysis::lint-rule-registry
  verible::verilog::parser::verilog-token-enum
)

add_library(uvm-macro-semicolon-rule STATIC uvm-macro-semicolon-rule.cc)
add_library(verible::verilog::analysis::checkers::uvm-macro-semicolon-rule ALIAS uvm-macro-semicolon-rule)
target_include_directories(uvm-macro-semicolon-rule PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(uvm-macro-semicolon-rule PUBLIC
  verible::common::analysis::lint-rule-status
  verible::common::analysis::syntax-tree-lint-rule
  verible::common::text::concrete-syntax-leaf
  verible::common::text::symbol
  verible::common::text::syntax-tree-context
  verible::common::text::token-info
  verible::verilog::CST::context-functions
  verible::verilog::CST::macro
  verible::verilog::CST::verilog-nonterminals
  verible::verilog::analysis::descriptions
  verible::verilog::analysis::lint-rule-registry
  verible::verilog::parser::verilog-token-enum
)

add_library(suspicious-semicolon-rule STATIC suspicious-semicolon-rule.cc)
add_library(verible::verilog::analysis::checkers::suspicious-semicolon-rule ALIAS suspicious-semicolon-rule)
target_include_directories(suspicious-semicolon-rule PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(suspicious-semicolon-rule PUBLIC
  verible::common::analysis::lint-rule-status
  verible::common::analysis::syntax-tree-lint-rule
  verible::common::analysis::matcher::bound-symbol-manager
  verible::common::text::concrete-syntax-tree
  verible::common::text::syntax-tree-context
  verible::common::text::tree-utils
  verible::verilog::CST::verilog-matchers
  verible::verilog::CST::verilog-nonterminals
  verible::verilog::analysis::descriptions
  verible::verilog::analysis::lint-rule-registry
)

add_library(dff-name-style-rule STATIC dff-name-style-rule.cc)
add_library(verible::verilog::analysis::checkers::dff-name-style-rule ALIAS dff-name-style-rule)
target_include_directories(dff-name-style-rule PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(dff-name-style-rule PUBLIC
  verible::common::analysis::lint-rule-status
  verible::common::analysis::syntax-tree-lint-rule
  verible::common::analysis::matcher::bound-symbol-manager
  verible::common::analysis::matcher::core-matchers
  verible::common::text::concrete-syntax-leaf
  verible::common::text::concrete-syntax-tree
  verible::common::text::config-utils
  verible::common::text::symbol
  verible::common::text::syntax-tree-context
  verible::common::text::token-info
  verible::common::text::tree-utils
  verible::verilog::CST::expression
  verible::verilog::CST::statement
  verible::verilog::CST::verilog-matchers
  verible::verilog::CST::verilog-nonterminals
  verible::verilog::analysis::descriptions
  verible::verilog::analysis::lint-rule-registry
  verible::verilog::parser::verilog-token-enum
)

