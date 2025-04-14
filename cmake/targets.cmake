function(cc_library)
    set(options OPTIONAL)
    set(oneValueArgs NAME)
    set(multiValueArgs SRCS INTERFACE_SRCS HDRS DEPS DEFINES)
    cmake_parse_arguments(PARSE_ARGV 0 arg
            "${options}" "${oneValueArgs}" "${multiValueArgs}"
    )

    set(target ${arg_NAME})
    cmake_path(RELATIVE_PATH CMAKE_CURRENT_LIST_DIR BASE_DIRECTORY "${CMAKE_SOURCE_DIR}" OUTPUT_VARIABLE current_dir)
    cmake_path(NORMAL_PATH current_dir)
    string(REPLACE "/" "::" current_prefix "${current_dir}")
    string(CONCAT target_with_namespace "${current_prefix}" "::" "${target}")

    if ("${arg_SRCS}" STREQUAL "")
        set(target_type "INTERFACE")
        set(target_visibility INTERFACE)
        set(target_options_visibility INTERFACE)
    else ()
        set(target_type "STATIC")
        set(target_visibility PUBLIC)
        set(target_options_visibility PRIVATE)
    endif ()

    add_library(${target} ${target_type} ${arg_SRCS})
    add_library(${target_with_namespace} ALIAS ${target})
    target_include_directories(${target} ${target_visibility} $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}> $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}>)
    target_compile_definitions(${target} ${target_options_visibility} "${arg_DEFINES}")
    target_link_libraries(${target} ${target_visibility} ${arg_DEPS})
    target_compile_features(${target} ${target_options_visibility} cxx_std_17)
    target_sources(${target} ${target_visibility} ${arg_INTERFACE_SRCS})
endfunction()

function(cc_test)
    set(options OPTIONAL)
    set(oneValueArgs NAME)
    set(multiValueArgs SRCS HDRS DEPS DEFINES)
    cmake_parse_arguments(PARSE_ARGV 0 arg
            "${options}" "${oneValueArgs}" "${multiValueArgs}"
    )

    if (NOT VERIBLE_TEST)
        return()
    endif ()

    set(target ${arg_NAME})

    add_executable(${target} ${arg_SRCS})
    target_link_libraries(${target} PRIVATE ${arg_DEPS})
    target_compile_definitions(${target} PRIVATE "${arg_DEFINES}")
    target_compile_features(${target} PRIVATE cxx_std_17)
    add_test(NAME ${target} COMMAND ${target})
endfunction()