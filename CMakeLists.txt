cmake_minimum_required(VERSION 3.16)
project(x64id C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "-O2")

set(COMMONS src/x64id.c src/utils/function_length.c src/vector.c src/queue.c src/utils/test_functions.c)
set(SOURCES src/main.c)

add_executable(x64id ${COMMONS} ${SOURCES})

include(test/CMakeLists.txt)