cmake_minimum_required(VERSION 3.24)
project(console_read)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")

add_executable(console_read
        solution.c)
target_link_libraries(console_read)