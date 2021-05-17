add_library(algorithms STATIC src/quicksort.c)

target_include_directories(algorithms PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
