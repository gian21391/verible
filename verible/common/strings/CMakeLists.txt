add_library(compare INTERFACE)
add_library(verible::common::strings::compare ALIAS compare)
target_include_directories(compare INTERFACE ${CMAKE_SOURCE_DIR})

add_library(comment-utils STATIC comment-utils.cc)
add_library(verible::common::strings::comment-utils ALIAS comment-utils)
target_include_directories(comment-utils PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(comment-utils PUBLIC
        verible::common::util::logging
        verible::common::util::range
        absl::strings
)

add_library(diff STATIC diff.cc)
add_library(verible::common::strings::diff ALIAS diff)
target_include_directories(diff PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(diff PUBLIC
        verible::common::strings::position
        verible::common::strings::split
        external_libs::editscript
        verible::common::util::iterator-range
)

add_library(display-utils STATIC display-utils.cc)
add_library(verible::common::strings::display-utils ALIAS display-utils)
target_include_directories(display-utils PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(display-utils PUBLIC
        absl::strings
)

add_library(obfuscator STATIC obfuscator.cc)
add_library(verible::common::strings::obfuscator ALIAS obfuscator)
target_include_directories(obfuscator PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(obfuscator PUBLIC
        verible::common::strings::compare
        verible::common::util::bijective-map
        verible::common::util::logging
        absl::status
        absl::strings
)

add_library(mem-block INTERFACE)
add_library(verible::common::strings::mem-block ALIAS mem-block)
target_include_directories(mem-block INTERFACE ${CMAKE_SOURCE_DIR})

add_library(naming-utils STATIC naming-utils.cc)
add_library(verible::common::strings::naming-utils ALIAS naming-utils)
target_include_directories(naming-utils PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(naming-utils PUBLIC
        absl::strings
)

add_library(patch STATIC patch.cc)
add_library(verible::common::strings::patch ALIAS patch)
target_include_directories(patch PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(patch PUBLIC
        verible::common::strings::compare
        verible::common::strings::position
        verible::common::strings::split
        verible::common::util::algorithm
        verible::common::util::container-iterator-range
        verible::common::util::file-util
        verible::common::util::iterator-adaptors
        verible::common::util::iterator-range
        verible::common::util::logging
        verible::common::util::status-macros
        verible::common::util::user-interaction
        absl::core_headers
        absl::status
        absl::statusor
        absl::strings
)

add_library(position STATIC position.cc)
add_library(verible::common::strings::position ALIAS position)
target_include_directories(position PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(position PUBLIC
        verible::common::util::interval
        verible::common::util::interval-set
)

add_library(random STATIC random.cc)
add_library(verible::common::strings::random ALIAS random)
target_include_directories(random PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(random PUBLIC
        verible::common::util::interval-set
        verible::common::util::iterator-range
        verible::common::util::logging
)

add_library(verible_common_strings_range STATIC range.cc)
add_library(verible::common::strings::range ALIAS verible_common_strings_range)
target_include_directories(verible_common_strings_range PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(verible_common_strings_range PUBLIC
        verible::common::util::logging
        verible::common::util::range
)

add_library(split STATIC split.cc)
add_library(verible::common::strings::split ALIAS split)
target_include_directories(split PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(split PUBLIC
        absl::strings
)

add_library(rebase STATIC rebase.cc)
add_library(verible::common::strings::rebase ALIAS rebase)
target_include_directories(rebase PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(rebase PUBLIC
        verible::common::util::logging
)

add_library(utf8 INTERFACE)
add_library(verible::common::strings::utf8 ALIAS utf8)
target_include_directories(utf8 INTERFACE ${CMAKE_SOURCE_DIR})

add_library(line-column-map STATIC line-column-map.cc)
add_library(verible::common::strings::line-column-map ALIAS line-column-map)
target_include_directories(line-column-map PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(line-column-map PUBLIC
        verible::common::strings::utf8
        absl::base
)

add_library(string-memory-map INTERFACE)
add_library(verible::common::strings::string-memory-map ALIAS string-memory-map)
target_include_directories(string-memory-map INTERFACE ${CMAKE_SOURCE_DIR})
target_link_libraries(string-memory-map INTERFACE
        verible::common::strings::range
        verible::common::util::interval-map
        verible::common::util::interval-set
        verible::common::util::logging
)

add_executable(compare_test compare_test.cc)
target_link_libraries(compare_test PRIVATE
        verible::common::strings::compare
        GTest::gtest
        GTest::gtest_main
)
add_test(NAME compare_test COMMAND compare_test)

add_executable(comment-utils_test comment-utils_test.cc)
target_link_libraries(comment-utils_test PRIVATE
        verible::common::strings::comment-utils
        verible::common::util::range
        GTest::gtest
        GTest::gtest_main
)
add_test(NAME comment-utils_test COMMAND comment-utils_test)

add_executable(diff_test diff_test.cc)
target_link_libraries(diff_test PRIVATE
        verible::common::strings::diff
        verible::common::strings::position
        external_libs::editscript
        GTest::gtest
        GTest::gtest_main
)
add_test(NAME diff_test COMMAND diff_test)

add_executable(display-utils_test display-utils_test.cc)
target_link_libraries(display-utils_test PRIVATE
        verible::common::strings::display-utils
        GTest::gtest
        GTest::gtest_main
)
add_test(NAME display-utils_test COMMAND display-utils_test)

add_executable(obfuscator_test obfuscator_test.cc)
target_link_libraries(obfuscator_test PRIVATE
        verible::common::strings::obfuscator
        verible::common::strings::random
        verible::common::util::bijective-map
        verible::common::util::logging
        absl::status
        GTest::gtest
        GTest::gtest_main
)
add_test(NAME obfuscator_test COMMAND obfuscator_test)

add_executable(naming-utils_test naming-utils_test.cc)
target_link_libraries(naming-utils_test PRIVATE
        verible::common::strings::naming-utils
        GTest::gtest
        GTest::gtest_main
)
add_test(NAME naming-utils_test COMMAND naming-utils_test)

add_executable(patch_test patch_test.cc)
target_link_libraries(patch_test PRIVATE
        verible::common::strings::patch
        verible::common::strings::position
        absl::status
        absl::statusor
        absl::strings
        GTest::gtest
        GTest::gtest_main
)
add_test(NAME patch_test COMMAND patch_test)

add_executable(position_test position_test.cc)
target_link_libraries(position_test PRIVATE
        verible::common::strings::position
        GTest::gtest
        GTest::gtest_main
)
add_test(NAME position_test COMMAND position_test)

add_executable(random_test random_test.cc)
target_link_libraries(random_test PRIVATE
        verible::common::strings::random
        GTest::gtest
        GTest::gtest_main
)
add_test(NAME random_test COMMAND random_test)

add_executable(verible_common_strings_range_test range_test.cc)
target_link_libraries(verible_common_strings_range_test PRIVATE
        verible::common::strings::range
        verible::common::util::range
        GTest::gtest
        GTest::gtest_main
)
add_test(NAME range_test COMMAND range_test)

add_executable(split_test split_test.cc)
target_link_libraries(split_test PRIVATE
        verible::common::strings::range
        verible::common::strings::split
        verible::common::util::range
        GTest::gtest
        GTest::gtest_main
)
add_test(NAME split_test COMMAND split_test)

add_executable(rebase_test rebase_test.cc)
target_link_libraries(rebase_test PRIVATE
        verible::common::strings::rebase
        verible::common::util::range
        GTest::gtest
        GTest::gtest_main
)
add_test(NAME rebase_test COMMAND rebase_test)

add_executable(utf8_test utf8_test.cc)
target_link_libraries(utf8_test PRIVATE
        verible::common::strings::utf8
        GTest::gtest
        GTest::gtest_main
)
add_test(NAME utf8_test COMMAND utf8_test)

add_executable(line-column-map_test line-column-map_test.cc)
target_link_libraries(line-column-map_test PRIVATE
        verible::common::strings::line-column-map
        absl::strings
        GTest::gtest
        GTest::gtest_main
)
add_test(NAME line-column-map_test COMMAND line-column-map_test)

add_executable(string-memory-map_test string-memory-map_test.cc)
target_link_libraries(string-memory-map_test PRIVATE
        verible::common::strings::range
        verible::common::strings::string-memory-map
        verible::common::util::logging
        verible::common::util::range
        GTest::gtest
        GTest::gtest_main
)
add_test(NAME string-memory-map_test COMMAND string-memory-map_test)