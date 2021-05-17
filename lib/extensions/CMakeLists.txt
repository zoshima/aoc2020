add_library(extensions STATIC src/string_extensions.cpp src/char_extensions.c)

target_include_directories(extensions PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
