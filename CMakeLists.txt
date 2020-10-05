cmake_minimum_required(VERSION 3.16)
project(fenice C)

set(CMAKE_C_STANDARD 11)
#set(CMAKE_C_FLAGS "-O3")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin/)

include_directories(include)

set(TEST_SOURCES src/main_test.c)
set(COMMONS src/fenice.c src/main_test.c)

add_executable(fenice ${COMMONS})
