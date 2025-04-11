flex_target(verilog_lexer
        ${CMAKE_CURRENT_SOURCE_DIR}/verilog.lex
        ${CMAKE_CURRENT_BINARY_DIR}/verilog.yy.cc
)

bison_target(verilog_parser
        ${CMAKE_CURRENT_SOURCE_DIR}/verilog.y
        ${CMAKE_CURRENT_BINARY_DIR}/verilog.tab.cc
        DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/verilog.tab.hh
        REPORT_FILE ${CMAKE_CURRENT_BINARY_DIR}/verilog.output
        COMPILE_FLAGS "--graph=${CMAKE_CURRENT_BINARY_DIR}/verilog.dot"
)
add_flex_bison_dependency(verilog_lexer verilog_parser)

add_custom_command(
        OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/verilog-token-enum.h
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_SOURCE_DIR}/cmake/gen_verilog_token_enum.py ${CMAKE_CURRENT_BINARY_DIR}/verilog.tab.hh ${CMAKE_CURRENT_BINARY_DIR}/verilog-token-enum.h
        DEPENDS ${BISON_verilog_parser_OUTPUTS}
)
add_custom_target(verilog-token-enum-gen DEPENDS
        ${CMAKE_CURRENT_BINARY_DIR}/verilog-token-enum.h
)

add_custom_command(
        OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/verilog-moved.tab.cc
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_SOURCE_DIR}/cmake/parser_utils.py std_move_parser_symbols --src "${CMAKE_CURRENT_BINARY_DIR}/verilog.tab.cc" --out "${CMAKE_CURRENT_BINARY_DIR}/verilog-moved.tab.cc"
        DEPENDS ${BISON_verilog_parser_OUTPUTS}
)
add_custom_target(verilog-moved-tab-gen DEPENDS
        ${CMAKE_CURRENT_BINARY_DIR}/verilog-moved.tab.cc
)

add_custom_command(
        OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/verilog-final.tab.cc
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_SOURCE_DIR}/cmake/parser_utils.py record_recovered_syntax_errors --src "${CMAKE_CURRENT_BINARY_DIR}/verilog-moved.tab.cc" --out "${CMAKE_CURRENT_BINARY_DIR}/verilog-final.tab.cc"
        DEPENDS verilog-moved-tab-gen
)
add_custom_target(verilog-final-tab-gen DEPENDS
        ${CMAKE_CURRENT_BINARY_DIR}/verilog-final.tab.cc
)

add_custom_command(
        OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/verilog-parse-interface.h
        COMMAND ${CMAKE_COMMAND} -E echo "// DO NOT EDIT -- generated from ${CMAKE_CURRENT_BINARY_DIR}/verilog.tab.hh" > ${CMAKE_CURRENT_BINARY_DIR}/verilog-parse-interface.h
        COMMAND sed -e "/#ifndef YYTOKENTYPE/,/#endif/d" ${CMAKE_CURRENT_BINARY_DIR}/verilog.tab.hh >> ${CMAKE_CURRENT_BINARY_DIR}/verilog-parse-interface.h
        DEPENDS ${BISON_verilog_parser_OUTPUTS}
)


cc_library(
        NAME
        "verilog-lexer"
        SRCS
        "verilog.yy.cc"
        "verilog-lexer.cc"
        DEPS
        verilog-token-enum
        command-file-lex-gen
        verible::common::lexer::flex-lexer-adapter
        verible::common::text::token-info
)

cc_test(
        NAME
        "verilog-lexer_test"
        SRCS
        "verilog-lexer_test.cc"
        DEPS
        verilog-lexer
        verilog-token-enum
        verible::common::lexer::lexer-test-util
        verible::common::text::token-info
        GTest::gtest
        GTest::gtest_main
)

cc_library(
        NAME
        "verilog-token-enum"
)
add_dependencies(verilog-token-enum verilog-token-enum-gen)

cc_library(
        NAME
        "verilog-y-cc"
        SRCS
        "verilog-final.tab.cc"
        DEPS
        verible::common::parser::bison-parser-common
        verible::common::parser::parser-param
        verible::common::text::tree-utils
        verible::common::util::casts
        verible::common::util::logging
        verible::verilog::CST::DPI
        verible::verilog::CST::declaration
        verible::verilog::CST::expression
        verible::verilog::CST::functions
        verible::verilog::CST::module
        verible::verilog::CST::parameters
        verible::verilog::CST::port
        verible::verilog::CST::type
        verible::verilog::CST::verilog-nonterminals
        verible::verilog::CST::verilog-treebuilder-utils
)

cc_library(
        NAME
        "verilog-parser"
        SRCS
        "verilog-parser.cc"
        DEPS
        verilog-y-cc
        verible::common::parser::bison-parser-adapter
        verible::common::parser::parse
        verible::common::parser::parser-param
        verible::common::util::value-saver
        absl::flags
)

cc_library(
        NAME
        "verilog-lexical-context"
        SRCS
        "verilog-lexical-context.cc"
        DEPS
        verilog-token-enum
        verible::common::text::token-info
        verible::common::text::token-stream-view
        verible::common::util::logging
        verible::common::util::with-reason
)

cc_test(
        NAME
        "verilog-parser_test"
        SRCS
        "verilog-parser_test.cc"
        DEPS
        verilog-token-enum
        verible::common::parser::bison-parser-common
        verible::common::parser::parser-test-util
        verible::common::text::constants
        verible::common::text::parser-verifier
        verible::common::text::symbol
        verible::common::text::token-info
        verible::common::text::token-info-test-util
        verible::common::util::logging
        verible::verilog::CST::verilog-nonterminals
        verible::verilog::analysis::verilog-analyzer
        verible::verilog::preprocessor::verilog-preprocess
        absl::status
        absl::strings
        GTest::gtest
        GTest::gtest_main
)

cc_test(
        NAME
        "verilog-lexical-context_test"
        SRCS
        "verilog-lexical-context_test.cc"
        DEPS
        verilog-lexical-context
        verilog-parser
        verilog-token-enum
        verible::common::text::text-structure
        verible::common::text::token-info
        verible::common::text::token-stream-view
        verible::common::util::logging
        verible::verilog::analysis::verilog-analyzer
        absl::strings
        GTest::gtest
        GTest::gtest_main
)

cc_library(
        NAME
        "verilog-token-classifications"
        SRCS
        "verilog-token-classifications.cc"
        DEPS
        verilog-token-enum
)

cc_test(
        NAME
        "verilog-token-classifications_test"
        SRCS
        "verilog-token-classifications_test.cc"
        DEPS
        verilog-token-classifications
        verilog-token-enum
        GTest::gtest
        GTest::gtest_main
)

cc_library(
        NAME
        "verilog-token"
        SRCS
        "verilog-token.cc"
        DEPS
        verilog-parser
        verilog-token-enum
)
