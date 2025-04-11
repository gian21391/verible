cc_library(
        NAME
        "algorithm"
)

cc_library(
        NAME
        "auto-pop-stack"
        DEPS
        logging
        absl::core_headers
)

cc_library(
        NAME
        "forward"
)

cc_library(
        NAME
        "range"
        DEPS
        logging
)

cc_library(
        NAME
        "status-macros"
        DEPS
        absl::core_headers
)

cc_library(
        NAME
        "subcommand"
        SRCS
        "subcommand.cc"
        DEPS
        container-iterator-range
        verible::common::strings::compare
        absl::status
        absl::strings
)

cc_library(
        NAME
        "thread-pool"
        SRCS
        "thread-pool.cc"
)

cc_library(
        NAME
        "file-util"
        SRCS
        "file-util.cc"
        DEPS
        logging
        verible::common::strings::mem-block
        absl::status
        absl::statusor
        absl::strings
)

if (DEFINED VERIBLE_COMMIT_TIMESTAMP AND DEFINED VERIBLE_GIT_DESCRIBE)
    add_custom_command(
            OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/generated-verible-build-version.h
            COMMAND ${Python3_EXECUTABLE} ${CMAKE_SOURCE_DIR}/cmake/build_version.py -c "${VERIBLE_COMMIT_TIMESTAMP}" -v "${VERIBLE_GIT_DESCRIBE}" > ${CMAKE_CURRENT_BINARY_DIR}/generated-verible-build-version.h
            COMMENT "Generating generated-verible-build-version.h"
    )
else ()
    add_custom_command(
            OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/generated-verible-build-version.h
            COMMAND ${Python3_EXECUTABLE} ${CMAKE_SOURCE_DIR}/cmake/build_version.py > ${CMAKE_CURRENT_BINARY_DIR}/generated-verible-build-version.h
            COMMENT "Generating generated-verible-build-version.h"
    )
endif ()


add_custom_target(generated-verible-build-version-gen
        DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/generated-verible-build-version.h
)

add_library(generated-verible-build-version-lib INTERFACE)
target_include_directories(generated-verible-build-version-lib INTERFACE ${CMAKE_BINARY_DIR})
add_dependencies(generated-verible-build-version-lib generated-verible-build-version-gen)

cc_library(
        NAME
        "build-version"
        DEPS
        generated-verible-build-version-lib
)

cc_library(
        NAME
        "init-command-line"
        SRCS
        "init-command-line.cc"
        DEPS
        build-version
        absl::failure_signal_handler
        absl::symbolize
        absl::flags_config
        absl::flags_parse
        absl::flags_usage
        absl::log_globals
        absl::log_severity
        absl::log_initialize
        absl::strings
        absl::time
)

cc_library(
        NAME
        "interval"
        DEPS
        forward
        absl::strings
)

cc_library(
        NAME
        "interval-map"
        DEPS
        auto-iterator
        logging
)

cc_library(
        NAME
        "interval-set"
        DEPS
        auto-iterator
        interval
        iterator-range
        logging
        absl::random_random
        absl::strings
)

cc_library(
        NAME
        "logging"
        DEPS
        absl::log
        absl::check
        absl::die_if_null
)

cc_library(
        NAME
        "casts"
)

cc_library(
        NAME
        "container-util"
        DEPS
        logging
)

cc_library(
        NAME
        "container-iterator-range"
        DEPS
        iterator-range
        range
)

cc_library(
        NAME
        "type-traits"
)

cc_library(
        NAME
        "auto-iterator"
)

cc_library(
        NAME
        "iterator-adaptors"
        DEPS
        auto-iterator
        iterator-range
)

cc_library(
        NAME
        "iterator-range"
        DEPS
)

cc_library(
        NAME
        "spacer"
        SRCS
        "spacer.cc"
)

cc_library(
        NAME
        "top-n"
)

cc_library(
        NAME
        "value-saver"
)

cc_library(
        NAME
        "enum-flags"
        DEPS
        bijective-map
        verible::common::strings::compare
        absl::strings
)

cc_library(
        NAME
        "bijective-map"
        DEPS
        logging
)

cc_library(
        NAME
        "vector-tree"
        DEPS
        container-proxy
        iterator-range
        logging
)

cc_library(
        NAME
        "tree-operations"
        SRCS
        "tree-operations.cc"
        DEPS
        logging
        spacer
        type-traits
        absl::strings
)

cc_library(
        NAME
        "expandable-tree-view"
        DEPS
        logging
        tree-operations
        vector-tree
)

cc_library(
        NAME
        "vector-tree-test-util"
        SRCS
        "vector-tree-test-util.cc"
        DEPS
        tree-operations
        vector-tree
        GTest::gtest
)

cc_library(
        NAME
        "vector-tree-iterators"
        DEPS
        iterator-range
        logging
        tree-operations
)

cc_library(
        NAME
        "map-tree"
        DEPS
        logging
        spacer
)

cc_library(
        NAME
        "with-reason"
)

cc_library(
        NAME
        "user-interaction"
        SRCS
        "user-interaction.cc"
)

cc_library(
        NAME
        "container-proxy"
)

cc_test(
        NAME
        "algorithm_test"
        SRCS
        "algorithm_test.cc"
        DEPS
        algorithm
        iterator-range
        GTest::gtest
        GTest::gtest_main
)

cc_test(
        NAME
        "auto-iterator_test"
        SRCS
        "auto-iterator_test.cc"
        DEPS
        auto-iterator
        GTest::gtest
        GTest::gtest_main
)

cc_test(
        NAME
        "auto-pop-stack_test"
        SRCS
        "auto-pop-stack_test.cc"
        DEPS
        auto-pop-stack
        iterator-range
        GTest::gtest
        GTest::gtest_main
)

cc_test(
        NAME
        "file-util_test"
        SRCS
        "file-util_test.cc"
        DEPS
        file-util
        absl::status
        absl::statusor
        absl::strings
        GTest::gtest
        GTest::gtest_main
)

cc_test(
        NAME
        "interval_test"
        SRCS
        "interval_test.cc"
        DEPS
        interval
        GTest::gtest
        GTest::gtest_main
)

cc_test(
        NAME
        "interval-map_test"
        SRCS
        "interval-map_test.cc"
        DEPS
        interval-map
        range
        GTest::gtest
        GTest::gtest_main
)

cc_test(
        NAME
        "interval-set_test"
        SRCS
        "interval-set_test.cc"
        DEPS
        interval
        interval-set
        logging
        GTest::gtest
        GTest::gtest_main
)

cc_test(
        NAME
        "forward_test"
        SRCS
        "forward_test.cc"
        DEPS
        forward
        GTest::gtest
        GTest::gtest_main
)

cc_test(
        NAME
        "range_test"
        SRCS
        "range_test.cc"
        DEPS
        iterator-range
        range
        GTest::gtest
        GTest::gtest_main
)

cc_test(
        NAME
        "thread-pool_test"
        SRCS
        "thread-pool_test.cc"
        DEPS
        thread-pool
        absl::time
        GTest::gtest
        GTest::gtest_main
)

cc_test(
        NAME
        "container-iterator-range_test"
        SRCS
        "container-iterator-range_test.cc"
        DEPS
        container-iterator-range
        GTest::gtest
        GTest::gtest_main
)

cc_test(
        NAME
        "iterator-adaptors_test"
        SRCS
        "iterator-adaptors_test.cc"
        DEPS
        iterator-adaptors
        iterator-range
        GTest::gtest
        GTest::gtest_main
)

cc_test(
        NAME
        "iterator-range_test"
        SRCS
        "iterator-range_test.cc"
        DEPS
        iterator-range
        range
        GTest::gtest
        GTest::gtest_main
)

cc_test(
        NAME
        "spacer_test"
        SRCS
        "spacer_test.cc"
        DEPS
        spacer
        GTest::gtest
        GTest::gtest_main
)

cc_test(
        NAME
        "subcommand_test"
        SRCS
        "subcommand_test.cc"
        DEPS
        subcommand
        absl::status
        absl::strings
        GTest::gtest
        GTest::gtest_main
)

cc_test(
        NAME
        "top-n_test"
        SRCS
        "top-n_test.cc"
        DEPS
        top-n
        GTest::gtest
        GTest::gtest_main
)

cc_test(
        NAME
        "type-traits_test"
        SRCS
        "type-traits_test.cc"
        DEPS
        type-traits
        GTest::gtest
        GTest::gtest_main
)

cc_test(
        NAME
        "value-saver_test"
        SRCS
        "value-saver_test.cc"
        DEPS
        value-saver
        GTest::gtest
        GTest::gtest_main
)

cc_test(
        NAME
        "enum-flags_test"
        SRCS
        "enum-flags_test.cc"
        DEPS
        enum-flags
        absl::strings
        GTest::gtest
        GTest::gtest_main
)

cc_test(
        NAME
        "bijective-map_test"
        SRCS
        "bijective-map_test.cc"
        DEPS
        bijective-map
        logging
        verible::common::strings::compare
        GTest::gtest
        GTest::gtest_main
)

cc_test(
        NAME
        "vector-tree_test"
        SRCS
        "vector-tree_test.cc"
        DEPS
        logging
        tree-operations
        vector-tree
        vector-tree-test-util
        absl::strings
        GTest::gtest
        GTest::gtest_main
)

foreach(shard RANGE 1 6)
    cc_test(
            NAME
            "tree-operations_${shard}_test"
            SRCS
            "tree-operations_test.cc"
            DEFINES
            COMPILATION_SHARD=${shard}
            DEPS
            logging
            spacer
            tree-operations
            type-traits
            absl::strings
            absl::str_format
            GTest::gtest
            GTest::gtest_main
    )
endforeach()

cc_test(
        NAME
        "expandable-tree-view_test"
        SRCS
        "expandable-tree-view_test.cc"
        DEPS
        expandable-tree-view
        vector-tree
        vector-tree-test-util
        absl::strings
        GTest::gtest
        GTest::gtest_main
)

cc_test(
        NAME
        "vector-tree-iterators_test"
        SRCS
        "vector-tree-iterators_test.cc"
        DEPS
        tree-operations
        vector-tree
        vector-tree-iterators
        absl::strings
        GTest::gtest
        GTest::gtest_main
)

cc_test(
        NAME
        "map-tree_test"
        SRCS
        "map-tree_test.cc"
        DEPS
        map-tree
        spacer
        GTest::gtest
        GTest::gtest_main
)

cc_test(
        NAME
        "with-reason_test"
        SRCS
        "with-reason_test.cc"
        DEPS
        with-reason
        GTest::gtest
        GTest::gtest_main
)

cc_test(
        NAME
        "user-interaction_test"
        SRCS
        "user-interaction_test.cc"
        DEPS
        user-interaction
        absl::strings
        GTest::gtest
        GTest::gtest_main
)

cc_test(
        NAME
        "container-proxy_test"
        SRCS
        "container-proxy_test.cc"
        DEPS
        container-proxy
        type-traits
        verible::common::strings::display-utils
        GTest::gtest
        GTest::gtest_main
)

cc_library(
        NAME
        "simple-zip"
        SRCS
        "simple-zip.cc"
        DEPS
        third_party::portable_endian
        ZLIB::ZLIB
)

cc_test(
        NAME
        "simple-zip_test"
        SRCS
        "simple-zip_test.cc"
        DEPS
        file-util
        simple-zip
        GTest::gtest
        GTest::gtest_main
)

cc_library(
        NAME
        "sha256"
        SRCS
        "sha256.cc"
        DEPS
        absl::strings
)

cc_test(
        NAME
        "sha256_test"
        SRCS
        "sha256_test.cc"
        DEPS
        sha256
        absl::strings
        GTest::gtest
        GTest::gtest_main
)