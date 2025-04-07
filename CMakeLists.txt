cmake_minimum_required(VERSION 3.20)
project(verible)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
if(WIN32)
    find_package(BISON)
    if(NOT BISON_FOUND)
        FetchContent_Declare(win_flex_bison
                URL https://github.com/lexxmark/winflexbison/releases/download/v2.5.25/win_flex_bison-2.5.25.zip
                URL_MD5 720226b1befe7033fb3ecc98f5ffd425
                DOWNLOAD_EXTRACT_TIMESTAMP TRUE
        )
        FetchContent_MakeAvailable(win_flex_bison)
        LIST(APPEND CMAKE_PROGRAM_PATH "${win_flex_bison_SOURCE_DIR}")
    endif ()
endif ()
find_package(FLEX REQUIRED)
find_package(BISON REQUIRED)
cmake_path(GET FLEX_EXECUTABLE PARENT_PATH FLEX_INCLUDE_DIR)

enable_testing()

find_package(absl CONFIG REQUIRED)
find_package(GTest CONFIG REQUIRED)
find_package(re2 CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(ZLIB REQUIRED)
find_package(Python3 REQUIRED COMPONENTS Interpreter)

file(GLOB_RECURSE V_GLOB LIST_DIRECTORIES true "*")
foreach(item ${V_GLOB})
    if(IS_DIRECTORY ${item})
        if(EXISTS "${item}/CMakeLists.txt")
            message("Adding: ${item}")
            add_subdirectory(${item})
        endif ()
    endif()
endforeach()
