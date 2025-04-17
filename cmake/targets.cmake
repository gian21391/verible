function(cc_library)
    set(options OPTIONAL)
    set(oneValueArgs NAME)
    set(multiValueArgs SRCS INTERFACE_SRCS HDRS DEPS DEFINES)
    cmake_parse_arguments(PARSE_ARGV 0 arg
            "${options}" "${oneValueArgs}" "${multiValueArgs}"
    )

    if (NOT VERIBLE_TEST AND ${arg_NAME} MATCHES ".*test.*")
        message("Not adding ${arg_NAME}")
        return()
    endif ()

    set(target ${arg_NAME})
    cmake_path(RELATIVE_PATH CMAKE_CURRENT_LIST_DIR BASE_DIRECTORY "${CMAKE_SOURCE_DIR}" OUTPUT_VARIABLE current_dir)
    cmake_path(NORMAL_PATH current_dir)
    string(REPLACE "/" "::" current_prefix "${current_dir}")
    string(CONCAT target_with_namespace "${current_prefix}" "::" "${target}")

    if ("${arg_SRCS}" STREQUAL "" AND "${arg_INTERFACE_SRCS}" STREQUAL "")
        set(target_type "INTERFACE")
        set(target_visibility INTERFACE)
        set(target_options_visibility INTERFACE)
    elseif ("${arg_SRCS}" STREQUAL "")
        set(target_type "OBJECT")
        set(target_visibility PUBLIC)
        set(target_options_visibility PUBLIC)
    else ()
        set(target_type "STATIC")
        set(target_visibility PUBLIC)
        set(target_options_visibility PRIVATE)
    endif ()

    set(object_files "")

    if (NOT "${arg_DEPS}" STREQUAL "")
        foreach (item ${arg_DEPS})
            set(aliased_target "$<TARGET_PROPERTY:${item},ALIASED_TARGET>")
            set(target_no_namespace "$<MAKE_C_IDENTIFIER:$<IF:$<BOOL:${aliased_target}>,${aliased_target},${item}>>")
            set(is_object_lib "$<STREQUAL:$<TARGET_PROPERTY:${item},TYPE>,OBJECT_LIBRARY>")
            list(APPEND object_files "$<${is_object_lib}:$<TARGET_OBJECTS:${item}>>")
        endforeach ()
    endif ()

    add_library(${target} ${target_type} ${arg_SRCS} ${arg_INTERFACE_SRCS})
    add_library(${target_with_namespace} ALIAS ${target})
    target_include_directories(${target} ${target_visibility}
            $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}>
            $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}>
            $<BUILD_INTERFACE:${FLEX_INCLUDE_DIR}>)
    target_compile_definitions(${target} ${target_options_visibility} "${arg_DEFINES}")
    target_link_libraries(${target} ${target_visibility} ${arg_DEPS} ${object_files})
    target_compile_features(${target} ${target_options_visibility} cxx_std_20)
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
    target_compile_features(${target} PRIVATE cxx_std_20)
    add_test(NAME ${target} COMMAND ${target})
endfunction()