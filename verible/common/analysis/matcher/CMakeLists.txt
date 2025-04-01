add_library(bound-symbol-manager STATIC bound-symbol-manager.cc)
add_library(verible::common::analysis::matcher::bound-symbol-manager ALIAS bound-symbol-manager)
target_include_directories(bound-symbol-manager PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(bound-symbol-manager PUBLIC
        verible::common::text::symbol
        verible::common::util::casts
        verible::common::util::container-util
        verible::common::util::logging
)

add_library(matcher STATIC matcher.cc)
add_library(verible::common::analysis::matcher::matcher ALIAS matcher)
target_include_directories(matcher PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(matcher PUBLIC
        verible::common::analysis::matcher::bound-symbol-manager
        verible::common::text::symbol
        absl::optional
)

add_library(core-matchers INTERFACE)
add_library(verible::common::analysis::matcher::core-matchers ALIAS core-matchers)
target_include_directories(core-matchers INTERFACE ${CMAKE_SOURCE_DIR})
target_link_libraries(core-matchers INTERFACE
        verible::common::analysis::matcher::inner-match-handlers
        verible::common::analysis::matcher::matcher
        verible::common::text::symbol
)

add_library(inner-match-handlers STATIC inner-match-handlers.cc)
add_library(verible::common::analysis::matcher::inner-match-handlers ALIAS inner-match-handlers)
target_include_directories(inner-match-handlers PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(inner-match-handlers PUBLIC
        verible::common::analysis::matcher::bound-symbol-manager
        verible::common::analysis::matcher::matcher
        verible::common::text::symbol
        verible::common::util::logging
)

add_library(matcher-builders INTERFACE)
add_library(verible::common::analysis::matcher::matcher-builders ALIAS matcher-builders)
target_include_directories(matcher-builders INTERFACE ${CMAKE_SOURCE_DIR})
target_link_libraries(matcher-builders INTERFACE
        verible::common::analysis::matcher::descent-path
        verible::common::analysis::matcher::inner-match-handlers
        verible::common::analysis::matcher::matcher
        verible::common::text::symbol
)

add_library(descent-path STATIC descent-path.cc)
add_library(verible::common::analysis::matcher::descent-path ALIAS descent-path)
target_include_directories(descent-path PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(descent-path PUBLIC
        verible::common::text::concrete-syntax-tree
        verible::common::text::symbol
        verible::common::util::casts
)

add_library(matcher-test-utils STATIC matcher-test-utils.cc)
add_library(verible::common::analysis::matcher::matcher-test-utils ALIAS matcher-test-utils)
target_include_directories(matcher-test-utils PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(matcher-test-utils PUBLIC
        verible::common::analysis::matcher::bound-symbol-manager
        verible::common::analysis::matcher::matcher
        verible::common::text::concrete-syntax-leaf
        verible::common::text::concrete-syntax-tree
        verible::common::text::symbol
        verible::common::text::tree-utils
        verible::common::text::visitors
        GTest::gtest
)