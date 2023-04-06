cmake_minimum_required(VERSION 3.16)
project(mca C)

set(COMMONS ${CMAKE_CURRENT_SOURCE_DIR}/src/mca.c ${CMAKE_CURRENT_SOURCE_DIR}/src/utils/function_length.c ${CMAKE_CURRENT_SOURCE_DIR}/src/vector.c ${CMAKE_CURRENT_SOURCE_DIR}/src/queue.c)

set(TEST_SOURCES test/main_test.c)

add_executable(mca_test ${COMMONS} ${TEST_SOURCES})

