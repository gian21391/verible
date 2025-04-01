add_library(editscript INTERFACE)
add_library(external_libs::editscript ALIAS editscript)
target_include_directories(editscript INTERFACE ${CMAKE_SOURCE_DIR})

add_executable(editscript_test editscript_test.cc)
target_link_libraries(editscript_test PRIVATE
        external_libs::editscript
        absl::strings
        GTest::gtest
        GTest::gtest_main
)
add_test(NAME editscript_test COMMAND editscript_test)