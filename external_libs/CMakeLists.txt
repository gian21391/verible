cc_library(
        NAME
        "editscript"
)

cc_test(
        NAME
        "editscript_test"
        SRCS
        "editscript_test.cc"
        DEPS
        editscript
        absl::strings
        GTest::gtest
        GTest::gtest_main
)
