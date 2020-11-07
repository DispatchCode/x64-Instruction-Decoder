cmake_minimum_required(VERSION 3.16)
project(mca C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "-O3")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin/)

set(COMMONS src/mca.c)
set(SOURCES src/main.c)

add_executable(mca ${COMMONS} ${SOURCES})

include(src/test/CMakeLists.txt)