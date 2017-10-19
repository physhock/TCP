cmake_minimum_required(VERSION 3.8)

set(SOURCES  wrap.c error.c readn.c writen.c str_cli.c str_echo.c)
set(HEADERS unp.h)
add_library(lib ${SOURCES} ${HEADERS})