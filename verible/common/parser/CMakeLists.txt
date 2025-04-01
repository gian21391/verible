add_library(parse INTERFACE)
add_library(verible::common::parser::parse ALIAS parse)
target_include_directories(parse INTERFACE ${CMAKE_SOURCE_DIR})
target_link_libraries(parse INTERFACE
        verible::common::text::concrete-syntax-tree
        verible::common::text::token-info
        absl::status
)

add_library(parser-param STATIC parser-param.cc)
add_library(verible::common::parser::parser-param ALIAS parser-param)
target_include_directories(parser-param PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(parser-param PUBLIC
        verible::common::lexer::token-generator
        verible::common::text::concrete-syntax-leaf
        verible::common::text::concrete-syntax-tree
        verible::common::text::token-info
        verible::common::util::casts
        verible::common::util::logging
)

add_library(bison-parser-adapter INTERFACE)
add_library(verible::common::parser::bison-parser-adapter ALIAS bison-parser-adapter)
target_include_directories(bison-parser-adapter INTERFACE ${CMAKE_SOURCE_DIR})
target_link_libraries(bison-parser-adapter INTERFACE
        verible::common::parser::parse
        verible::common::parser::parser-param
        verible::common::lexer::token-generator
        verible::common::text::concrete-syntax-tree
        verible::common::text::token-info
        verible::common::util::logging
        absl::status
)

add_library(bison-parser-common STATIC bison-parser-common.cc)
add_library(verible::common::parser::bison-parser-common ALIAS bison-parser-common)
target_include_directories(bison-parser-common PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(bison-parser-common PUBLIC
        verible::common::parser::parser-param
        verible::common::text::concrete-syntax-leaf
        verible::common::text::concrete-syntax-tree
        verible::common::text::token-info
        verible::common::util::logging
)


add_library(parser-test-util INTERFACE)
add_library(verible::common::parser::parser-test-util ALIAS parser-test-util)
target_include_directories(parser-test-util INTERFACE ${CMAKE_SOURCE_DIR})
target_link_libraries(parser-test-util INTERFACE
        verible::common::analysis::matcher::descent-path
        verible::common::text::parser-verifier
        verible::common::text::symbol
        verible::common::text::token-info-test-util
        verible::common::util::logging
        absl::status
        GTest::gtest
)

add_executable(bison-parser-common_test bison-parser-common_test.cc)
target_include_directories(bison-parser-common_test PRIVATE ${CMAKE_SOURCE_DIR})
target_link_libraries(bison-parser-common_test PRIVATE
        verible::common::parser::bison-parser-common
        verible::common::parser::parser-param
        verible::common::lexer::flex-lexer-adapter
        verible::common::lexer::token-stream-adapter
        verible::common::text::concrete-syntax-leaf
        verible::common::text::concrete-syntax-tree
        verible::common::text::symbol
        verible::common::text::token-info
        verible::common::util::casts
        GTest::gtest
        GTest::gtest_main
)
add_test(NAME bison-parser-common_test COMMAND bison-parser-common_test)