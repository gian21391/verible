add_library(algorithm INTERFACE)
add_library(verible::common::util::algorithm ALIAS algorithm)
target_include_directories(algorithm INTERFACE ${CMAKE_SOURCE_DIR})

add_library(auto-pop-stack INTERFACE)
add_library(verible::common::util::auto-pop-stack ALIAS auto-pop-stack)
target_include_directories(auto-pop-stack INTERFACE ${CMAKE_SOURCE_DIR})
target_link_libraries(auto-pop-stack INTERFACE
        verible::common::util::logging
        absl::core_headers
)

add_library(forward INTERFACE)
add_library(verible::common::util::forward ALIAS forward)
target_include_directories(forward INTERFACE ${CMAKE_SOURCE_DIR})

add_library(range INTERFACE)
add_library(verible::common::util::range ALIAS range)
target_include_directories(range INTERFACE ${CMAKE_SOURCE_DIR})
target_link_libraries(range INTERFACE
        verible::common::util::logging
)

add_library(status-macros INTERFACE)
add_library(verible::common::util::status-macros ALIAS status-macros)
target_include_directories(status-macros INTERFACE ${CMAKE_SOURCE_DIR})
target_link_libraries(status-macros INTERFACE
        absl::core_headers
)

add_library(subcommand STATIC subcommand.cc)
add_library(verible::common::util::subcommand ALIAS subcommand)
target_include_directories(subcommand PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(subcommand PUBLIC
        verible::common::util::container-iterator-range
        verible::common::strings::compare
        absl::status
        absl::strings
)

add_library(thread-pool STATIC thread-pool.cc)
add_library(verible::common::util::thread-pool ALIAS thread-pool)
target_include_directories(thread-pool PUBLIC ${CMAKE_SOURCE_DIR})
if(NOT WIN32)
    target_compile_options(thread-pool PRIVATE -fexceptions)
endif()

add_library(file-util STATIC file-util.cc)
add_library(verible::common::util::file-util ALIAS file-util)
target_include_directories(file-util PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(file-util PUBLIC
        verible::common::util::logging
        verible::common::strings::mem-block
        absl::status
        absl::statusor
        absl::strings
)

add_custom_command(
        OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/generated-verible-build-version.h
        COMMAND python ${CMAKE_SOURCE_DIR}/cmake/build_version.py > ${CMAKE_CURRENT_BINARY_DIR}/generated-verible-build-version.h
        COMMENT "Generating generated-verible-build-version.h"
)

add_custom_target(generated-verible-build-version-gen
        DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/generated-verible-build-version.h
)

add_library(build-version INTERFACE)
add_library(verible::common::util::build-version ALIAS build-version)
target_include_directories(build-version INTERFACE
        ${CMAKE_BINARY_DIR}
)
add_dependencies(build-version generated-verible-build-version-gen)

add_library(init-command-line STATIC init-command-line.cc)
add_library(verible::common::util::init-command-line ALIAS init-command-line)
target_include_directories(init-command-line PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(init-command-line PUBLIC
        verible::common::util::build-version
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

add_library(interval INTERFACE)
add_library(verible::common::util::interval ALIAS interval)
target_include_directories(interval INTERFACE ${CMAKE_SOURCE_DIR})
target_link_libraries(interval INTERFACE
        verible::common::util::forward
        absl::strings
)

add_library(interval-map INTERFACE)
add_library(verible::common::util::interval-map ALIAS interval-map)
target_include_directories(interval-map INTERFACE ${CMAKE_SOURCE_DIR})
target_link_libraries(interval-map INTERFACE
        verible::common::util::auto-iterator
        verible::common::util::logging
)

add_library(interval-set INTERFACE)
add_library(verible::common::util::interval-set ALIAS interval-set)
target_include_directories(interval-set INTERFACE ${CMAKE_SOURCE_DIR})
target_link_libraries(interval-set INTERFACE
        verible::common::util::auto-iterator
        verible::common::util::interval
        verible::common::util::iterator-range
        verible::common::util::logging
        absl::base
)

add_library(logging INTERFACE)
add_library(verible::common::util::logging ALIAS logging)
target_include_directories(logging INTERFACE ${CMAKE_SOURCE_DIR})
target_link_libraries(logging INTERFACE
        absl::base
)

add_library(casts INTERFACE)
add_library(verible::common::util::casts ALIAS casts)
target_include_directories(casts INTERFACE ${CMAKE_SOURCE_DIR})

add_library(container-util INTERFACE)
add_library(verible::common::util::container-util ALIAS container-util)
target_include_directories(container-util INTERFACE ${CMAKE_SOURCE_DIR})
target_link_libraries(container-util INTERFACE
        verible::common::util::logging
)

add_library(container-iterator-range INTERFACE)
add_library(verible::common::util::container-iterator-range ALIAS container-iterator-range)
target_include_directories(container-iterator-range INTERFACE ${CMAKE_SOURCE_DIR})
target_link_libraries(container-iterator-range INTERFACE
        verible::common::util::iterator-range
        verible::common::util::range
)

add_library(type-traits INTERFACE)
add_library(verible::common::util::type-traits ALIAS type-traits)
target_include_directories(type-traits INTERFACE ${CMAKE_SOURCE_DIR})

add_library(auto-iterator INTERFACE)
add_library(verible::common::util::auto-iterator ALIAS auto-iterator)
target_include_directories(auto-iterator INTERFACE ${CMAKE_SOURCE_DIR})

add_library(iterator-adaptors INTERFACE)
add_library(verible::common::util::iterator-adaptors ALIAS iterator-adaptors)
target_include_directories(iterator-adaptors INTERFACE ${CMAKE_SOURCE_DIR})
target_link_libraries(iterator-adaptors INTERFACE
        verible::common::util::auto-iterator
        verible::common::util::iterator-range
)

add_library(iterator-range INTERFACE)
add_library(verible::common::util::iterator-range ALIAS iterator-range)
target_include_directories(iterator-range INTERFACE ${CMAKE_SOURCE_DIR})

add_library(spacer STATIC spacer.cc)
add_library(verible::common::util::spacer ALIAS spacer)
target_include_directories(spacer PUBLIC ${CMAKE_SOURCE_DIR})

add_library(top-n INTERFACE)
add_library(verible::common::util::top-n ALIAS top-n)
target_include_directories(top-n INTERFACE ${CMAKE_SOURCE_DIR})

add_library(value-saver INTERFACE)
add_library(verible::common::util::value-saver ALIAS value-saver)
target_include_directories(value-saver INTERFACE ${CMAKE_SOURCE_DIR})

add_library(enum-flags INTERFACE)
add_library(verible::common::util::enum-flags ALIAS enum-flags)
target_include_directories(enum-flags INTERFACE ${CMAKE_SOURCE_DIR})
target_link_libraries(enum-flags INTERFACE
        verible::common::util::bijective-map
        verible::common::strings::compare
        absl::strings
)

add_library(bijective-map INTERFACE)
add_library(verible::common::util::bijective-map ALIAS bijective-map)
target_include_directories(bijective-map INTERFACE ${CMAKE_SOURCE_DIR})
target_link_libraries(bijective-map INTERFACE
        verible::common::util::logging
)

add_library(vector-tree INTERFACE)
add_library(verible::common::util::vector-tree ALIAS vector-tree)
target_include_directories(vector-tree INTERFACE ${CMAKE_SOURCE_DIR})
target_link_libraries(vector-tree INTERFACE
        verible::common::util::container-proxy
        verible::common::util::iterator-range
        verible::common::util::logging
)

add_library(tree-operations STATIC tree-operations.cc)
add_library(verible::common::util::tree-operations ALIAS tree-operations)
target_include_directories(tree-operations PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(tree-operations PUBLIC
        verible::common::util::logging
        verible::common::util::spacer
        verible::common::util::type-traits
        absl::strings
)

add_library(expandable-tree-view INTERFACE)
add_library(verible::common::util::expandable-tree-view ALIAS expandable-tree-view)
target_include_directories(expandable-tree-view INTERFACE ${CMAKE_SOURCE_DIR})
target_link_libraries(expandable-tree-view INTERFACE
        verible::common::util::logging
        verible::common::util::tree-operations
        verible::common::util::vector-tree
)

add_library(vector-tree-test-util STATIC vector-tree-test-util.cc)
add_library(verible::common::util::vector-tree-test-util ALIAS vector-tree-test-util)
target_include_directories(vector-tree-test-util PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(vector-tree-test-util PUBLIC
        verible::common::util::tree-operations
        verible::common::util::vector-tree
        GTest::gtest
)

add_library(vector-tree-iterators INTERFACE)
add_library(verible::common::util::vector-tree-iterators ALIAS vector-tree-iterators)
target_include_directories(vector-tree-iterators INTERFACE ${CMAKE_SOURCE_DIR})
target_link_libraries(vector-tree-iterators INTERFACE
        verible::common::util::iterator-range
        verible::common::util::logging
        verible::common::util::tree-operations
)

add_library(map-tree INTERFACE)
add_library(verible::common::util::map-tree ALIAS map-tree)
target_include_directories(map-tree INTERFACE ${CMAKE_SOURCE_DIR})
target_link_libraries(map-tree INTERFACE
        verible::common::util::logging
        verible::common::util::spacer
)

add_library(with-reason INTERFACE)
add_library(verible::common::util::with-reason ALIAS with-reason)
target_include_directories(with-reason INTERFACE ${CMAKE_SOURCE_DIR})

add_library(user-interaction STATIC user-interaction.cc)
add_library(verible::common::util::user-interaction ALIAS user-interaction)
target_include_directories(user-interaction PUBLIC ${CMAKE_SOURCE_DIR})

add_library(container-proxy INTERFACE)
add_library(verible::common::util::container-proxy ALIAS container-proxy)
target_include_directories(container-proxy INTERFACE ${CMAKE_SOURCE_DIR})

add_library(simple-zip STATIC simple-zip.cc)
add_library(verible::common::util::simple-zip ALIAS simple-zip)
target_include_directories(simple-zip PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(simple-zip PUBLIC
        third_party::portable_endian
        ZLIB::ZLIB
)

add_library(sha256 STATIC sha256.cc)
add_library(verible::common::util::sha256 ALIAS sha256)
target_include_directories(sha256 PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(sha256 PUBLIC
        absl::strings
)

add_executable(algorithm_test algorithm_test.cc)
target_link_libraries(algorithm_test PRIVATE
        verible::common::util::algorithm
        verible::common::util::iterator-range
        GTest::gtest
        GTest::gtest_main
)
add_test(NAME algorithm_test COMMAND algorithm_test)

add_executable(auto-iterator_test auto-iterator_test.cc)
target_link_libraries(auto-iterator_test PRIVATE
        verible::common::util::auto-iterator
        GTest::gtest
        GTest::gtest_main
)
add_test(NAME auto-iterator_test COMMAND auto-iterator_test)

add_executable(auto-pop-stack_test auto-pop-stack_test.cc)
target_link_libraries(auto-pop-stack_test PRIVATE
        verible::common::util::auto-pop-stack
        verible::common::util::iterator-range
        GTest::gtest
        GTest::gtest_main
)
add_test(NAME auto-pop-stack_test COMMAND auto-pop-stack_test)

add_executable(file-util_test file-util_test.cc)
target_link_libraries(file-util_test PRIVATE
        verible::common::util::file-util
        absl::status
        absl::statusor
        absl::strings
        GTest::gtest
        GTest::gtest_main
)
add_test(NAME file-util_test COMMAND file-util_test)

add_executable(interval_test interval_test.cc)
target_link_libraries(interval_test PRIVATE
        verible::common::util::interval
        GTest::gtest
        GTest::gtest_main
)
add_test(NAME interval_test COMMAND interval_test)

add_executable(interval-map_test interval-map_test.cc)
target_link_libraries(interval-map_test PRIVATE
        verible::common::util::interval-map
        verible::common::util::range
        GTest::gtest
        GTest::gtest_main
)
add_test(NAME interval-map_test COMMAND interval-map_test)

add_executable(interval-set_test interval-set_test.cc)
target_link_libraries(interval-set_test PRIVATE
        verible::common::util::interval
        verible::common::util::interval-set
        verible::common::util::logging
        GTest::gtest
        GTest::gtest_main
)
add_test(NAME interval-set_test COMMAND interval-set_test)

add_executable(forward_test forward_test.cc)
target_link_libraries(forward_test PRIVATE
        verible::common::util::forward
        GTest::gtest
        GTest::gtest_main
)
add_test(NAME forward_test COMMAND forward_test)

add_executable(range_test range_test.cc)
target_link_libraries(range_test PRIVATE
        verible::common::util::iterator-range
        verible::common::util::range
        GTest::gtest
        GTest::gtest_main
)
add_test(NAME range_test COMMAND range_test)

add_executable(thread-pool_test thread-pool_test.cc)
target_link_libraries(thread-pool_test PRIVATE
        verible::common::util::thread-pool
        absl::time
        GTest::gtest
        GTest::gtest_main
)
if(NOT WIN32)
    target_compile_options(thread-pool_test PRIVATE -fexceptions)
endif()
add_test(NAME thread-pool_test COMMAND thread-pool_test)

add_executable(container-iterator-range_test container-iterator-range_test.cc)
target_link_libraries(container-iterator-range_test PRIVATE
        verible::common::util::container-iterator-range
        GTest::gtest
        GTest::gtest_main
)
add_test(NAME container-iterator-range_test COMMAND container-iterator-range_test)

add_executable(iterator-adaptors_test iterator-adaptors_test.cc)
target_link_libraries(iterator-adaptors_test PRIVATE
        verible::common::util::iterator-adaptors
        verible::common::util::iterator-range
        GTest::gtest
        GTest::gtest_main
)
add_test(NAME iterator-adaptors_test COMMAND iterator-adaptors_test)

add_executable(iterator-range_test iterator-range_test.cc)
target_link_libraries(iterator-range_test PRIVATE
        verible::common::util::iterator-range
        verible::common::util::range
        GTest::gtest
        GTest::gtest_main
)
add_test(NAME iterator-range_test COMMAND iterator-range_test)

add_executable(spacer_test spacer_test.cc)
target_link_libraries(spacer_test PRIVATE
        verible::common::util::spacer
        GTest::gtest
        GTest::gtest_main
)
add_test(NAME spacer_test COMMAND spacer_test)

add_executable(subcommand_test subcommand_test.cc)
target_link_libraries(subcommand_test PRIVATE
        verible::common::util::subcommand
        absl::status
        absl::strings
        GTest::gtest
        GTest::gtest_main
)
add_test(NAME subcommand_test COMMAND subcommand_test)

add_executable(top-n_test top-n_test.cc)
target_link_libraries(top-n_test PRIVATE
        verible::common::util::top-n
        GTest::gtest
        GTest::gtest_main
)
add_test(NAME top-n_test COMMAND top-n_test)

add_executable(type-traits_test type-traits_test.cc)
target_link_libraries(type-traits_test PRIVATE
        verible::common::util::type-traits
        GTest::gtest
        GTest::gtest_main
)
add_test(NAME type-traits_test COMMAND type-traits_test)

add_executable(value-saver_test value-saver_test.cc)
target_link_libraries(value-saver_test PRIVATE
        verible::common::util::value-saver
        GTest::gtest
        GTest::gtest_main
)
add_test(NAME value-saver_test COMMAND value-saver_test)

add_executable(enum-flags_test enum-flags_test.cc)
target_link_libraries(enum-flags_test PRIVATE
        verible::common::util::enum-flags
        absl::strings
        GTest::gtest
        GTest::gtest_main
)
add_test(NAME enum-flags_test COMMAND enum-flags_test)

add_executable(bijective-map_test bijective-map_test.cc)
target_link_libraries(bijective-map_test PRIVATE
        verible::common::util::bijective-map
        verible::common::util::logging
        verible::common::strings::compare
        GTest::gtest
        GTest::gtest_main
)
add_test(NAME bijective-map_test COMMAND bijective-map_test)

add_executable(vector-tree_test vector-tree_test.cc)
target_link_libraries(vector-tree_test PRIVATE
        verible::common::util::logging
        verible::common::util::tree-operations
        verible::common::util::vector-tree
        verible::common::util::vector-tree-test-util
        absl::strings
        GTest::gtest
        GTest::gtest_main
)
add_test(NAME vector-tree_test COMMAND vector-tree_test)

# Handle the tree-operations sharded tests
foreach(shard RANGE 1 6)
    add_executable(tree-operations_${shard}_test tree-operations_test.cc)
    target_compile_definitions(tree-operations_${shard}_test PRIVATE COMPILATION_SHARD=${shard})
    target_link_libraries(tree-operations_${shard}_test PRIVATE
            verible::common::util::logging
            verible::common::util::spacer
            verible::common::util::tree-operations
            verible::common::util::type-traits
            absl::strings
            absl::str_format
            GTest::gtest
            GTest::gtest_main
    )
    add_test(NAME tree-operations_${shard}_test COMMAND tree-operations_${shard}_test)
endforeach()

add_executable(expandable-tree-view_test expandable-tree-view_test.cc)
target_link_libraries(expandable-tree-view_test PRIVATE
        verible::common::util::expandable-tree-view
        verible::common::util::vector-tree
        verible::common::util::vector-tree-test-util
        absl::strings
        GTest::gtest
        GTest::gtest_main
)
add_test(NAME expandable-tree-view_test COMMAND expandable-tree-view_test)

add_executable(vector-tree-iterators_test vector-tree-iterators_test.cc)
target_link_libraries(vector-tree-iterators_test PRIVATE
        verible::common::util::tree-operations
        verible::common::util::vector-tree
        verible::common::util::vector-tree-iterators
        absl::strings
        GTest::gtest
        GTest::gtest_main
)
add_test(NAME vector-tree-iterators_test COMMAND vector-tree-iterators_test)

add_executable(map-tree_test map-tree_test.cc)
target_link_libraries(map-tree_test PRIVATE
        verible::common::util::map-tree
        verible::common::util::spacer
        GTest::gtest
        GTest::gtest_main
)
if(NOT WIN32)
    target_compile_options(map-tree_test PRIVATE -Wno-array-bounds)
endif()
add_test(NAME map-tree_test COMMAND map-tree_test)

add_executable(with-reason_test with-reason_test.cc)
target_link_libraries(with-reason_test PRIVATE
        verible::common::util::with-reason
        GTest::gtest
        GTest::gtest_main
)
add_test(NAME with-reason_test COMMAND with-reason_test)

add_executable(user-interaction_test user-interaction_test.cc)
target_link_libraries(user-interaction_test PRIVATE
        verible::common::util::user-interaction
        absl::strings
        GTest::gtest
        GTest::gtest_main
)
add_test(NAME user-interaction_test COMMAND user-interaction_test)

add_executable(container-proxy_test container-proxy_test.cc)
target_link_libraries(container-proxy_test PRIVATE
        verible::common::util::container-proxy
        verible::common::util::type-traits
        verible::common::strings::display-utils
        GTest::gtest
        GTest::gtest_main
)
add_test(NAME container-proxy_test COMMAND container-proxy_test)

add_executable(simple-zip_test simple-zip_test.cc)
target_link_libraries(simple-zip_test PRIVATE
        verible::common::util::file-util
        verible::common::util::simple-zip
        GTest::gtest
        GTest::gtest_main
)
add_test(NAME simple-zip_test COMMAND simple-zip_test)

add_executable(sha256_test sha256_test.cc)
target_link_libraries(sha256_test PRIVATE
        verible::common::util::sha256
        absl::strings
        GTest::gtest
        GTest::gtest_main
)
add_test(NAME sha256_test COMMAND sha256_test)