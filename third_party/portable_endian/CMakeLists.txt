add_library(portable_endian INTERFACE)
add_library(third_party::portable_endian ALIAS portable_endian)
target_include_directories(portable_endian INTERFACE ${CMAKE_SOURCE_DIR})