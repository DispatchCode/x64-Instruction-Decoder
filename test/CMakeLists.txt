cmake_minimum_required(VERSION 3.16)
project(mca C)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin/test)

set(COMMONS ../src/mca.c)
set(TEST_SOURCES test/main_test.c)

add_executable(mca_test ${COMMONS} ${TEST_SOURCES})