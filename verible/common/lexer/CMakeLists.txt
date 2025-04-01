add_library(token-generator INTERFACE)
add_library(verible::common::lexer::token-generator ALIAS token-generator)
target_include_directories(token-generator INTERFACE ${CMAKE_SOURCE_DIR})
target_link_libraries(token-generator INTERFACE
        verible::common::text::token-info
)

add_library(token-stream-adapter STATIC token-stream-adapter.cc)
add_library(verible::common::lexer::token-stream-adapter ALIAS token-stream-adapter)
target_include_directories(token-stream-adapter PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(token-stream-adapter PUBLIC
        verible::common::lexer::lexer
        verible::common::lexer::token-generator
        verible::common::text::token-info
        verible::common::text::token-stream-view
        absl::status
)

add_library(flex-lexer-adapter INTERFACE)
add_library(verible::common::lexer::flex-lexer-adapter ALIAS flex-lexer-adapter)
target_include_directories(flex-lexer-adapter INTERFACE ${CMAKE_SOURCE_DIR})
target_link_libraries(flex-lexer-adapter INTERFACE
        verible::common::lexer::lexer
        verible::common::text::token-info
        verible::common::util::logging
        absl::base
)

add_library(lexer INTERFACE)
add_library(verible::common::lexer::lexer ALIAS lexer)
target_include_directories(lexer INTERFACE ${CMAKE_SOURCE_DIR})
target_link_libraries(lexer INTERFACE
        verible::common::text::token-info
)

add_library(lexer-test-util STATIC lexer-test-util.cc)
add_library(verible::common::lexer::lexer-test-util ALIAS lexer-test-util)
target_include_directories(lexer-test-util PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(lexer-test-util PUBLIC
        verible::common::text::constants
        verible::common::text::token-info
        verible::common::text::token-info-test-util
        verible::common::util::logging
        GTest::gtest
)

add_executable(lexer-test-util_test lexer-test-util_test.cc)
target_link_libraries(lexer-test-util_test PRIVATE
        verible::common::lexer::lexer-test-util
        verible::common::text::constants
        verible::common::text::token-info
        absl::strings
        GTest::gtest
        GTest::gtest_main
)
add_test(NAME lexer-test-util_test COMMAND lexer-test-util_test)

add_executable(token-stream-adapter_test token-stream-adapter_test.cc)
target_link_libraries(token-stream-adapter_test PRIVATE
        verible::common::lexer::lexer
        verible::common::lexer::lexer-test-util
        verible::common::lexer::token-stream-adapter
        verible::common::text::constants
        verible::common::text::token-info
        verible::common::text::token-stream-view
        absl::status
        GTest::gtest
        GTest::gtest_main
)
add_test(NAME token-stream-adapter_test COMMAND token-stream-adapter_test)