cmake_minimum_required(VERSION 3.16)
project(mca C)

set(COMMONS ../src/mca.c)
set(TEST_SOURCES test/main_test.c)

add_executable(mca_test ${COMMONS} ${TEST_SOURCES})