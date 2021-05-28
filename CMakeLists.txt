cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(AoC2020)

add_subdirectory(lib/extensions)
add_subdirectory(lib/algorithms)

include_directories(include)
# link_directories(${CMAKE_SOURCE_DIR/lib})

# add_executable(day1 src/day1.c)
# add_executable(day2 src/day2.c)
# add_executable(day3 src/day3.c)
# add_executable(day4 src/day4.c)
# add_executable(day5 src/day5.c)
# add_executable(day6 src/day6.c)

add_executable(day7 src/day7.cpp)
add_executable(day8 src/day8.cpp)
add_executable(day9 src/day9.cpp)
add_executable(day10 src/day10.cpp)
add_executable(day11 src/day11.cpp src/room.cpp)
add_executable(day12 src/day12.cpp)
add_executable(day13 src/day13.cpp)

# target_link_libraries(day4 PUBLIC extensions)
# target_link_libraries(day5 PUBLIC algorithms)
target_link_libraries(day7 PUBLIC extensions)
