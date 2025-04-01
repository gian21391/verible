add_library(verilog-preprocess STATIC verilog-preprocess.cc)
add_library(verible::verilog::preprocessor::verilog-preprocess ALIAS verilog-preprocess)
target_include_directories(verilog-preprocess PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(verilog-preprocess PUBLIC
        verible::common::lexer::token-generator
        verible::common::lexer::token-stream-adapter
        verible::common::text::macro-definition
        verible::common::text::text-structure
        verible::common::text::token-info
        verible::common::text::token-stream-view
        verible::common::util::container-util
        verible::common::util::logging
        verible::common::util::status-macros
        verible::verilog::analysis::verilog-filelist
        verible::verilog::parser::verilog-lexer
        verible::verilog::parser::verilog-parser
        verible::verilog::parser::verilog-token-enum
        absl::statusor
)