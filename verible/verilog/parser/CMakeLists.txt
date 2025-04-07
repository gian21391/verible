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



#add_custom_command(
#        OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/verilog-moved.tab.cc
#        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_BINARY_DIR}/verilog.tab.cc ${CMAKE_CURRENT_BINARY_DIR}/verilog-moved.tab.cc.tmp
#        COMMAND sed -e "s/std::move\\s*(/std::move(/g" ${CMAKE_CURRENT_BINARY_DIR}/verilog-moved.tab.cc.tmp > ${CMAKE_CURRENT_BINARY_DIR}/verilog-moved.tab.cc
#        DEPENDS ${BISON_verilog_parser_OUTPUTS}
#)
#
#add_custom_command(
#        OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/verilog-final.tab.cc
#        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_BINARY_DIR}/verilog-moved.tab.cc ${CMAKE_CURRENT_BINARY_DIR}/verilog-final.tab.cc.tmp
#        COMMAND sed -e "/^yyerrlab1:/,/goto yyerrlab1;/{/goto yyerrlab1;/!{/goto yyerrlab1/!p;};}" ${CMAKE_CURRENT_BINARY_DIR}/verilog-final.tab.cc.tmp > ${CMAKE_CURRENT_BINARY_DIR}/verilog-final.tab.cc
#        DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/verilog-moved.tab.cc
#)

add_library(verilog-token-enum INTERFACE)
add_library(verible::verilog::parser::verilog-token-enum ALIAS verilog-token-enum)
target_include_directories(verilog-token-enum INTERFACE
        ${CMAKE_SOURCE_DIR}
        ${CMAKE_BINARY_DIR}
)
add_dependencies(verilog-token-enum verilog-token-enum-gen)

add_library(verilog-lexer STATIC
        ${FLEX_verilog_lexer_OUTPUTS}
        verilog-lexer.cc
)
add_library(verible::verilog::parser::verilog-lexer ALIAS verilog-lexer)
target_include_directories(verilog-lexer PUBLIC
        ${FLEX_INCLUDE_DIR}
        ${CMAKE_SOURCE_DIR}
        ${CMAKE_CURRENT_BINARY_DIR}
)
if(NOT WIN32)
    target_compile_options(verilog-lexer PRIVATE -Wno-implicit-fallthrough)
endif()
target_link_libraries(verilog-lexer PUBLIC
        verible::verilog::parser::verilog-token-enum
        verible::common::lexer::flex-lexer-adapter
        verible::common::text::token-info
)

add_library(verilog-y-cc STATIC
        ${CMAKE_CURRENT_BINARY_DIR}/verilog-final.tab.cc
)
add_library(verible::verilog::parser::verilog-y-cc ALIAS verilog-y-cc)
target_include_directories(verilog-y-cc PUBLIC
        ${CMAKE_SOURCE_DIR}
        ${CMAKE_CURRENT_BINARY_DIR}
)
if(NOT WIN32)
    target_compile_options(verilog-y-cc PRIVATE
            -Wno-implicit-fallthrough
            -Wno-type-limits
            -Wno-unreachable-code
    )
endif()
target_link_libraries(verilog-y-cc PUBLIC
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
set_target_properties(verilog-y-cc PROPERTIES LINKER_LANGUAGE CXX)

add_library(verilog-parser STATIC verilog-parser.cc)
add_library(verible::verilog::parser::verilog-parser ALIAS verilog-parser)
target_include_directories(verilog-parser PUBLIC
        ${CMAKE_SOURCE_DIR}
        ${CMAKE_CURRENT_BINARY_DIR}
)
target_link_libraries(verilog-parser PUBLIC
        verible::verilog::parser::verilog-y-cc
        verible::common::parser::bison-parser-adapter
        verible::common::parser::parse
        verible::common::parser::parser-param
        verible::common::util::value-saver
        absl::flags
)

add_library(verilog-lexical-context STATIC verilog-lexical-context.cc)
add_library(verible::verilog::parser::verilog-lexical-context ALIAS verilog-lexical-context)
target_include_directories(verilog-lexical-context PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(verilog-lexical-context PUBLIC
        verible::verilog::parser::verilog-token-enum
        verible::common::text::token-info
        verible::common::text::token-stream-view
        verible::common::util::logging
        verible::common::util::with-reason
)

add_library(verilog-token-classifications STATIC verilog-token-classifications.cc)
add_library(verible::verilog::parser::verilog-token-classifications ALIAS verilog-token-classifications)
target_include_directories(verilog-token-classifications PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(verilog-token-classifications PUBLIC
        verible::verilog::parser::verilog-token-enum
)

add_library(verilog-token STATIC verilog-token.cc)
add_library(verible::verilog::parser::verilog-token ALIAS verilog-token)
target_include_directories(verilog-token PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(verilog-token PUBLIC
        verible::verilog::parser::verilog-parser
        verible::verilog::parser::verilog-token-enum
)

add_executable(verilog-lexer_test verilog-lexer_test.cc)
target_link_libraries(verilog-lexer_test PRIVATE
        verible::verilog::parser::verilog-lexer
        verible::verilog::parser::verilog-token-enum
        verible::common::lexer::lexer-test-util
        verible::common::text::token-info
        GTest::gtest
        GTest::gtest_main
)
add_test(NAME verilog-lexer_test COMMAND verilog-lexer_test)

add_executable(verilog-parser_test verilog-parser_test.cc)
target_link_libraries(verilog-parser_test PRIVATE
        verible::verilog::parser::verilog-token-enum
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
add_test(NAME verilog-parser_test COMMAND verilog-parser_test)

add_executable(verilog-lexical-context_test verilog-lexical-context_test.cc)
target_link_libraries(verilog-lexical-context_test PRIVATE
        verible::verilog::parser::verilog-lexical-context
        verible::verilog::parser::verilog-parser
        verible::verilog::parser::verilog-token-enum
        verible::common::text::text-structure
        verible::common::text::token-info
        verible::common::text::token-stream-view
        verible::common::util::logging
        verible::verilog::analysis::verilog-analyzer
        absl::strings
        GTest::gtest
        GTest::gtest_main
)
add_test(NAME verilog-lexical-context_test COMMAND verilog-lexical-context_test)

add_executable(verilog-token-classifications_test verilog-token-classifications_test.cc)
target_link_libraries(verilog-token-classifications_test PRIVATE
        verible::verilog::parser::verilog-token-classifications
        verible::verilog::parser::verilog-token-enum
        GTest::gtest
        GTest::gtest_main
)
add_test(NAME verilog-token-classifications_test COMMAND verilog-token-classifications_test)