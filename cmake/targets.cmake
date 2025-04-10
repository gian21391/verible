function(cc_library)
    set(options OPTIONAL)
    set(oneValueArgs NAME)
    set(multiValueArgs SRCS HDRS DEPS)
    cmake_parse_arguments(PARSE_ARGV 0 arg
            "${options}" "${oneValueArgs}" "${multiValueArgs}"
    )

    set(target ${arg_NAME})
#    string(CONCAT target ${target} "__testing")
    cmake_path(RELATIVE_PATH CMAKE_CURRENT_LIST_DIR BASE_DIRECTORY "${CMAKE_SOURCE_DIR}" OUTPUT_VARIABLE current_dir)
    cmake_path(NORMAL_PATH current_dir)
    string(REPLACE "/" "::" current_prefix "${current_dir}")
    string(CONCAT target_with_namespace "${current_prefix}" "::" "${target}")

    if ("${arg_SRCS}" STREQUAL "")
        set(target_type "INTERFACE")
        set(target_visibility INTERFACE)
    else ()
        set(target_type "STATIC")
        set(target_visibility PUBLIC)
    endif ()

    add_library(${target} ${target_type} ${arg_SRCS})
    add_library(${target_with_namespace} ALIAS ${target})
    target_include_directories(${target} ${target_visibility} ${CMAKE_SOURCE_DIR} ${CMAKE_BINARY_DIR})
    target_link_libraries(${target} ${target_visibility} ${arg_DEPS})
endfunction()

function(cc_test)
    set(options OPTIONAL)
    set(oneValueArgs NAME)
    set(multiValueArgs SRCS HDRS DEPS)
    cmake_parse_arguments(PARSE_ARGV 0 arg
            "${options}" "${oneValueArgs}" "${multiValueArgs}"
    )

    set(target ${arg_NAME})
#    string(CONCAT target ${target} "__testing")

    add_executable(${target} ${arg_SRCS})
    target_link_libraries(${target} PUBLIC ${arg_DEPS})
    add_test(NAME ${target} COMMAND ${target})
endfunction()