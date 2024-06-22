cmake_minimum_required(VERSION 3.16)
project(x64id C)

set(COMMONS ${CMAKE_CURRENT_SOURCE_DIR}/src/x64id.c ${CMAKE_CURRENT_SOURCE_DIR}/src/utils/function_length.c ${CMAKE_CURRENT_SOURCE_DIR}/src/vector.c ${CMAKE_CURRENT_SOURCE_DIR}/src/queue.c)

set(TEST_SOURCES test/main_test.c)

add_executable(x64id_test ${COMMONS} ${TEST_SOURCES})

