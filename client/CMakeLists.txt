cmake_minimum_required(VERSION 3.8)
add_executable(client main.c)
include_directories(../lib)
target_link_libraries(client lib)
