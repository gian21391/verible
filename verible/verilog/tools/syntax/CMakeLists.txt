add_executable(verible-verilog-syntax verilog-syntax.cc)
target_link_libraries(verible-verilog-syntax PRIVATE
        verible::common::strings::mem-block
        verible::common::text::concrete-syntax-tree
        verible::common::text::parser-verifier
        verible::common::text::text-structure
        verible::common::text::token-info
        verible::common::text::token-info-json
        verible::common::util::enum-flags
        verible::common::util::file-util
        verible::common::util::init-command-line
        verible::common::util::iterator-range
        verible::common::util::logging
        verible::verilog::CST::verilog-tree-json
        verible::verilog::CST::verilog-tree-print
        verible::verilog::analysis::json-diagnostics
        verible::verilog::analysis::verilog-analyzer
        verible::verilog::analysis::checkers::verilog-lint-rules
        verible::verilog::parser::verilog-parser
        verible::verilog::parser::verilog-token
        verible::verilog::parser::verilog-token-classifications
        verible::verilog::parser::verilog-token-enum
        absl::base
        nlohmann_json::nlohmann_json
)
target_include_directories(verible-verilog-syntax PRIVATE ${CMAKE_SOURCE_DIR})

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    target_link_options(verible-verilog-syntax PRIVATE -static)
endif()

## Add test
#add_test(
#        NAME verilog-syntax_test
#        COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/verilog_syntax_test.sh
#        $<TARGET_FILE:verible-verilog-syntax>
#)
