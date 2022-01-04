cmake_minimum_required(VERSION 3.16)
project(mca C)

set(CMAKE_C_STANDARD 11)
#set(CMAKE_C_FLAGS "-O2")

set(COMMONS src/mca.c src/utils/function_length.c src/vector.c src/queue.c src/utils/test_functions.c)
set(SOURCES src/main.c)

add_executable(mca ${COMMONS} ${SOURCES})

include(test/CMakeLists.txt)