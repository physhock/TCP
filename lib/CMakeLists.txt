cmake_minimum_required(VERSION 3.8)


find_package(Threads)
set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} -pthread)
set(SOURCES  wrap.c error.c str_cli.c str_echo.c readline.c)
set(HEADERS unp.h)
add_library(lib ${SOURCES} ${HEADERS})
target_link_libraries(lib Threads::Threads)