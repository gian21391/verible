function(generate_extract_nonterminals_script)
    set(script_content [[
# Read the input file
file(READ "${INPUT_FILE}" content)

# Process each line
file(STRINGS "${INPUT_FILE}" lines)

set(capture FALSE)
set(processed_content "")

foreach(line IN LISTS lines)
  if(line MATCHES "BEGIN GENERATE")
    set(capture TRUE)
    continue()
  endif()

  if(capture)
    if(line MATCHES "END GENERATE")
      set(capture FALSE)
      continue()
    endif()

    string(REGEX REPLACE "^ +" "CONSIDER(" line "${line}")
    string(REGEX REPLACE " =.*," "," line "${line}")
    string(REGEX REPLACE "," ")" line "${line}")

    string(APPEND processed_content "${line}\n")
  endif()
endforeach()

# Write the transformed content to the output file
file(WRITE "${OUTPUT_FILE}" "${processed_content}")
]])

    file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/extract_nonterminals.cmake" "${script_content}")
endfunction()

generate_extract_nonterminals_script()

set(NONTERMINALS_INPUT "${CMAKE_CURRENT_SOURCE_DIR}/verilog-nonterminals.h")
set(NONTERMINALS_OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/verilog_nonterminals_foreach-gen.inc")

add_custom_command(
        OUTPUT ${NONTERMINALS_OUTPUT}
        DEPENDS ${NONTERMINALS_INPUT}
        COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_BINARY_DIR}
        COMMAND ${CMAKE_COMMAND} -DINPUT_FILE=${NONTERMINALS_INPUT} -DOUTPUT_FILE=${NONTERMINALS_OUTPUT} -P ${CMAKE_CURRENT_BINARY_DIR}/extract_nonterminals.cmake
        COMMENT "Generating verilog_nonterminals_foreach-gen.inc"
)

add_custom_target(verilog-nonterminals-foreach-gen
        DEPENDS ${NONTERMINALS_OUTPUT}
)

add_library(verilog-nonterminals STATIC verilog-nonterminals.cc ${CMAKE_CURRENT_BINARY_DIR}/verilog_nonterminals_foreach-gen.inc)
add_library(verible::verilog::CST::verilog-nonterminals ALIAS verilog-nonterminals)
target_include_directories(verilog-nonterminals PUBLIC ${CMAKE_SOURCE_DIR} ${CMAKE_BINARY_DIR})
target_link_libraries(verilog-nonterminals PUBLIC
        verible::common::text::constants
        absl::base
)
add_dependencies(verilog-nonterminals verilog-nonterminals-foreach-gen)

add_library(verilog-matchers INTERFACE)
add_library(verible::verilog::CST::verilog-matchers ALIAS verilog-matchers)
target_include_directories(verilog-matchers INTERFACE ${CMAKE_SOURCE_DIR})
target_link_libraries(verilog-matchers INTERFACE
        verible::verilog::CST::verilog-nonterminals
        verible::common::analysis::matcher::matcher-builders
        verible::common::text::symbol
        verible::verilog::parser::verilog-token-enum
)

add_library(verilog-treebuilder-utils STATIC verilog-treebuilder-utils.cc)
add_library(verible::verilog::CST::verilog-treebuilder-utils ALIAS verilog-treebuilder-utils)
target_include_directories(verilog-treebuilder-utils PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(verilog-treebuilder-utils PUBLIC
        verible::verilog::CST::verilog-nonterminals
        verible::common::text::concrete-syntax-leaf
        verible::common::text::concrete-syntax-tree
        verible::common::text::symbol
        verible::common::text::token-info
        verible::common::util::logging
)

add_library(match-test-utils STATIC match-test-utils.cc)
add_library(verible::verilog::CST::match-test-utils ALIAS match-test-utils)
target_include_directories(match-test-utils PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(match-test-utils PUBLIC
        verible::common::analysis::syntax-tree-search
        verible::common::analysis::syntax-tree-search-test-utils
        verible::common::text::text-structure
        verible::verilog::analysis::verilog-analyzer
        GTest::gtest
)

add_library(constraints STATIC constraints.cc)
add_library(verible::verilog::CST::constraints ALIAS constraints)
target_include_directories(constraints PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(constraints PUBLIC
        verible::verilog::CST::identifier
        verible::verilog::CST::verilog-matchers
        verible::verilog::CST::verilog-nonterminals
        verible::common::analysis::syntax-tree-search
        verible::common::text::concrete-syntax-leaf
        verible::common::text::concrete-syntax-tree
        verible::common::text::symbol
        verible::common::text::token-info
        verible::common::text::tree-utils
)

add_library(DPI STATIC DPI.cc)
add_library(verible::verilog::CST::DPI ALIAS DPI)
target_include_directories(DPI PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(DPI PUBLIC
        verible::verilog::CST::verilog-matchers
        verible::verilog::CST::verilog-nonterminals
        verible::common::analysis::syntax-tree-search
        verible::common::text::concrete-syntax-tree
        verible::common::text::symbol
        verible::common::text::symbol-ptr
        verible::common::text::tree-utils
        verible::common::util::logging
        verible::verilog::parser::verilog-token-classifications
        verible::verilog::parser::verilog-token-enum
)

add_library(declaration STATIC declaration.cc)
add_library(verible::verilog::CST::declaration ALIAS declaration)
target_include_directories(declaration PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(declaration PUBLIC
        verible::verilog::CST::identifier
        verible::verilog::CST::type
        verible::verilog::CST::verilog-matchers
        verible::verilog::CST::verilog-nonterminals
        verible::common::analysis::syntax-tree-search
        verible::common::text::concrete-syntax-leaf
        verible::common::text::concrete-syntax-tree
        verible::common::text::constants
        verible::common::text::symbol
        verible::common::text::symbol-ptr
        verible::common::text::token-info
        verible::common::text::tree-utils
        verible::common::util::container-util
        verible::verilog::parser::verilog-token-enum
)

add_library(dimensions STATIC dimensions.cc)
add_library(verible::verilog::CST::dimensions ALIAS dimensions)
target_include_directories(dimensions PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(dimensions PUBLIC
        verible::verilog::CST::verilog-matchers
        # fixdeps:: keep
        verible::verilog::CST::verilog-nonterminals
        verible::common::analysis::syntax-tree-search
        verible::common::text::concrete-syntax-tree
        verible::common::text::symbol
        verible::common::text::tree-utils
)

add_library(expression STATIC expression.cc)
add_library(verible::verilog::CST::expression ALIAS expression)
target_include_directories(expression PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(expression PUBLIC
        verible::verilog::CST::type
        verible::verilog::CST::verilog-matchers
        verible::verilog::CST::verilog-nonterminals
        verible::common::analysis::syntax-tree-search
        verible::common::text::concrete-syntax-leaf
        verible::common::text::concrete-syntax-tree
        verible::common::text::symbol
        verible::common::text::token-info
        verible::common::text::tree-utils
        verible::common::util::casts
        verible::verilog::parser::verilog-token-classifications
        verible::verilog::parser::verilog-token-enum
)

add_library(functions STATIC functions.cc)
add_library(verible::verilog::CST::functions ALIAS functions)
target_include_directories(functions PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(functions PUBLIC
        verible::verilog::CST::identifier
        verible::verilog::CST::type
        verible::verilog::CST::verilog-matchers
        # fixdeps:: keep
        verible::verilog::CST::verilog-nonterminals
        verible::verilog::CST::verilog-treebuilder-utils
        verible::common::analysis::syntax-tree-search
        verible::common::text::concrete-syntax-leaf
        verible::common::text::concrete-syntax-tree
        verible::common::text::symbol
        verible::common::text::tree-utils
)

add_library(identifier STATIC identifier.cc)
add_library(verible::verilog::CST::identifier ALIAS identifier)
target_include_directories(identifier PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(identifier PUBLIC
        verible::verilog::CST::verilog-matchers
        # fixdeps:: keep
        verible::verilog::CST::verilog-nonterminals
        verible::common::analysis::syntax-tree-search
        verible::common::text::concrete-syntax-leaf
        verible::common::text::concrete-syntax-tree
        verible::common::text::symbol
        verible::common::text::tree-utils
        verible::common::util::casts
        verible::common::util::logging
        verible::verilog::parser::verilog-token-classifications
        verible::verilog::parser::verilog-token-enum
)

add_executable(identifier_test identifier_test.cc)
target_link_libraries(identifier_test PRIVATE
        verible::verilog::CST::identifier
        verible::verilog::CST::match-test-utils
        verible::common::analysis::syntax-tree-search
        verible::common::analysis::syntax-tree-search-test-utils
        verible::common::text::concrete-syntax-leaf
        verible::common::text::text-structure
        verible::common::util::logging
        verible::verilog::analysis::verilog-analyzer
        GTest::gtest
        GTest::gtest_main
)
add_test(NAME identifier_test COMMAND identifier_test)

add_library(macro STATIC macro.cc)
add_library(verible::verilog::CST::macro ALIAS macro)
target_include_directories(macro PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(macro PUBLIC
        verible::verilog::CST::verilog-matchers
        verible::verilog::CST::verilog-nonterminals
        verible::common::analysis::syntax-tree-search
        verible::common::text::concrete-syntax-leaf
        verible::common::text::concrete-syntax-tree
        verible::common::text::symbol
        verible::common::text::token-info
        verible::common::text::tree-utils
        verible::common::text::visitors
        verible::common::util::logging
        verible::verilog::parser::verilog-token-enum
)

add_library(class STATIC class.cc)
add_library(verible::verilog::CST::class ALIAS class)
target_include_directories(class PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(class PUBLIC
        verible::verilog::CST::identifier
        verible::verilog::CST::verilog-matchers
        # fixdeps:: keep
        verible::verilog::CST::verilog-nonterminals
        verible::common::analysis::syntax-tree-search
        verible::common::text::concrete-syntax-leaf
        verible::common::text::concrete-syntax-tree
        verible::common::text::symbol
        verible::common::text::tree-utils
        verible::common::text::visitors
)

add_library(module STATIC module.cc)
add_library(verible::verilog::CST::module ALIAS module)
target_include_directories(module PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(module PUBLIC
        verible::verilog::CST::verilog-matchers
        # fixdeps:: keep
        verible::verilog::CST::verilog-nonterminals
        verible::common::analysis::syntax-tree-search
        verible::common::text::concrete-syntax-leaf
        verible::common::text::concrete-syntax-tree
        verible::common::text::symbol
        verible::common::text::token-info
        verible::common::text::tree-utils
        verible::common::util::logging
)

add_library(net STATIC net.cc)
add_library(verible::verilog::CST::net ALIAS net)
target_include_directories(net PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(net PUBLIC
        verible::verilog::CST::identifier
        verible::verilog::CST::verilog-matchers
        # fixdeps:: keep
        verible::verilog::CST::verilog-nonterminals
        verible::common::analysis::syntax-tree-search
        verible::common::analysis::matcher::inner-match-handlers
        verible::common::text::concrete-syntax-leaf
        verible::common::text::concrete-syntax-tree
        verible::common::text::symbol
        verible::common::text::token-info
        verible::common::text::tree-utils
)

add_library(data STATIC data.cc)
add_library(verible::verilog::CST::data ALIAS data)
target_include_directories(data PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(data PUBLIC
        verible::verilog::CST::identifier
        verible::verilog::CST::verilog-matchers
        # fixdeps:: keep
        verible::verilog::CST::verilog-nonterminals
        verible::common::analysis::syntax-tree-search
        verible::common::analysis::matcher::inner-match-handlers
        verible::common::text::concrete-syntax-leaf
        verible::common::text::concrete-syntax-tree
        verible::common::text::symbol
        verible::common::text::token-info
        verible::common::text::tree-utils
)

add_library(package STATIC package.cc)
add_library(verible::verilog::CST::package ALIAS package)
target_include_directories(package PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(package PUBLIC
        verible::verilog::CST::verilog-matchers
        verible::verilog::CST::verilog-nonterminals
        verible::common::analysis::syntax-tree-search
        verible::common::text::concrete-syntax-leaf
        verible::common::text::concrete-syntax-tree
        verible::common::text::symbol
        verible::common::text::token-info
        verible::common::text::tree-utils
        verible::verilog::parser::verilog-token-enum
)

add_library(parameters STATIC parameters.cc)
add_library(verible::verilog::CST::parameters ALIAS parameters)
target_include_directories(parameters PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(parameters PUBLIC
        verible::verilog::CST::identifier
        verible::verilog::CST::verilog-matchers
        # fixdeps:: keep
        verible::verilog::CST::verilog-nonterminals
        verible::common::analysis::syntax-tree-search
        verible::common::text::concrete-syntax-leaf
        verible::common::text::concrete-syntax-tree
        verible::common::text::symbol
        verible::common::text::token-info
        verible::common::text::tree-utils
        verible::common::util::casts
        verible::common::util::logging
        verible::verilog::parser::verilog-token-enum
)

add_library(port STATIC port.cc)
add_library(verible::verilog::CST::port ALIAS port)
target_include_directories(port PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(port PUBLIC
        verible::verilog::CST::identifier
        verible::verilog::CST::verilog-matchers
        # fixdeps:: keep
        verible::verilog::CST::verilog-nonterminals
        verible::common::analysis::syntax-tree-search
        verible::common::text::concrete-syntax-leaf
        verible::common::text::concrete-syntax-tree
        verible::common::text::symbol
        verible::common::text::tree-utils
        verible::common::util::logging
)

add_library(seq-block STATIC seq-block.cc)
add_library(verible::verilog::CST::seq-block ALIAS seq-block)
target_include_directories(seq-block PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(seq-block PUBLIC
        verible::verilog::CST::verilog-nonterminals
        verible::common::text::concrete-syntax-leaf
        verible::common::text::concrete-syntax-tree
        verible::common::text::symbol
        verible::common::text::syntax-tree-context
        verible::common::text::token-info
        verible::common::text::tree-utils
        verible::common::util::logging
        verible::verilog::parser::verilog-token-enum
)

add_library(statement STATIC statement.cc)
add_library(verible::verilog::CST::statement ALIAS statement)
target_include_directories(statement PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(statement PUBLIC
        verible::verilog::CST::declaration
        verible::verilog::CST::identifier
        verible::verilog::CST::type
        verible::verilog::CST::verilog-matchers
        # fixdeps:: keep
        verible::verilog::CST::verilog-nonterminals
        verible::common::analysis::syntax-tree-search
        verible::common::text::concrete-syntax-leaf
        verible::common::text::concrete-syntax-tree
        verible::common::text::symbol
        verible::common::text::tree-utils
        verible::common::text::visitors
)

add_library(tasks STATIC tasks.cc)
add_library(verible::verilog::CST::tasks ALIAS tasks)
target_include_directories(tasks PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(tasks PUBLIC
        verible::verilog::CST::identifier
        verible::verilog::CST::verilog-matchers
        # fixdeps:: keep
        verible::verilog::CST::verilog-nonterminals
        verible::common::analysis::syntax-tree-search
        verible::common::text::concrete-syntax-leaf
        verible::common::text::concrete-syntax-tree
        verible::common::text::symbol
        verible::common::text::tree-utils
)

add_library(type STATIC type.cc)
add_library(verible::verilog::CST::type ALIAS type)
target_include_directories(type PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(type PUBLIC
        verible::verilog::CST::identifier
        verible::verilog::CST::verilog-matchers
        # fixdeps:: keep
        verible::verilog::CST::verilog-nonterminals
        verible::common::analysis::syntax-tree-search
        verible::common::text::concrete-syntax-leaf
        verible::common::text::concrete-syntax-tree
        verible::common::text::symbol
        verible::common::text::symbol-ptr
        verible::common::text::tree-utils
        verible::common::util::logging
        verible::verilog::parser::verilog-token-enum
)

add_library(context-functions INTERFACE)
add_library(verible::verilog::CST::context-functions ALIAS context-functions)
target_include_directories(context-functions INTERFACE ${CMAKE_SOURCE_DIR})
target_link_libraries(context-functions INTERFACE
        verible::verilog::CST::verilog-nonterminals
        verible::common::text::syntax-tree-context
)

add_library(numbers STATIC numbers.cc)
add_library(verible::verilog::CST::numbers ALIAS numbers)
target_include_directories(numbers PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(numbers PUBLIC
        verible::common::util::logging
)

add_library(verilog-tree-print STATIC verilog-tree-print.cc)
add_library(verible::verilog::CST::verilog-tree-print ALIAS verilog-tree-print)
target_include_directories(verilog-tree-print PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(verilog-tree-print PUBLIC
        verible::verilog::CST::verilog-nonterminals
        verible::common::text::concrete-syntax-leaf
        verible::common::text::concrete-syntax-tree
        verible::common::text::symbol
        verible::common::text::token-info
        verible::common::text::tree-utils
        verible::common::util::value-saver
        verible::verilog::parser::verilog-parser
)

add_library(verilog-tree-json STATIC verilog-tree-json.cc)
add_library(verible::verilog::CST::verilog-tree-json ALIAS verilog-tree-json)
target_include_directories(verilog-tree-json PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(verilog-tree-json PUBLIC
        verible::verilog::CST::verilog-nonterminals
        verible::common::text::concrete-syntax-leaf
        verible::common::text::concrete-syntax-tree
        verible::common::text::symbol
        verible::common::text::token-info
        verible::common::text::token-info-json
        verible::common::text::visitors
        verible::common::util::value-saver
        verible::verilog::parser::verilog-token
        verible::verilog::parser::verilog-token-classifications
        verible::verilog::parser::verilog-token-enum
        nlohmann_json::nlohmann_json
)
