cmake_minimum_required(VERSION 3.16)
project(mca C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "-O3")

set(COMMONS src/mca.c)
set(SOURCES src/main.c)

add_executable(mca ${COMMONS} ${SOURCES})

include(test/CMakeLists.txt)