cmake_minimum_required(VERSION 3.16)
project(mca C)

set(CMAKE_C_STANDARD 11)
#set(CMAKE_C_FLAGS "-O3")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin/test)

include_directories(include)

set(TEST_SOURCES src/main_test.c)
set(COMMONS src/mca.c src/main_test.c)

add_executable(mca ${COMMONS})
