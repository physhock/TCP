cmake_minimum_required(VERSION 3.8)
add_executable(server server.c)
include_directories(../lib)
target_link_libraries(server lib)