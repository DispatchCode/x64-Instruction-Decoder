cmake_minimum_required(VERSION 3.16)
project(x64id C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "-O2")

set(COMMONS src/x64id.c src/disasm.c src/utils/function_length.c src/vector.c src/queue.c src/utils/test_functions.c)
set(SOURCES src/main.c)

add_executable(x64id ${COMMONS} ${SOURCES})
add_executable(x64id_disassembler ${COMMONS}
	src/main_disassembler.c src/disassembler.c src/disassembler_output.c)

include(test/CMakeLists.txt)

# Format C sources before compiling either executable
find_program(CLANG_FORMAT_EXECUTABLE NAMES clang-format)
if(NOT CLANG_FORMAT_EXECUTABLE AND UNIX)
    # Some distributions install only versioned binaries, such as
    # clang-format-22, without providing a generic clang-format symlink
    # eg openSUSE Tumbleweed
    string(REPLACE ":" ";" CLANG_FORMAT_PATH_DIRS "$ENV{PATH}")
    set(CLANG_FORMAT_CANDIDATES)
    foreach(PATH_DIR IN LISTS CLANG_FORMAT_PATH_DIRS)
        file(GLOB PATH_CANDIDATES "${PATH_DIR}/clang-format-*")
        list(APPEND CLANG_FORMAT_CANDIDATES ${PATH_CANDIDATES})
    endforeach()
    list(SORT CLANG_FORMAT_CANDIDATES COMPARE NATURAL ORDER DESCENDING)

    foreach(CANDIDATE IN LISTS CLANG_FORMAT_CANDIDATES)
        execute_process(
            COMMAND "${CANDIDATE}" --version
            RESULT_VARIABLE CANDIDATE_RESULT
            OUTPUT_QUIET
            ERROR_QUIET
        )
        if(CANDIDATE_RESULT EQUAL 0)
            set(CLANG_FORMAT_EXECUTABLE "${CANDIDATE}")
            break()
        endif()
    endforeach()
endif()
if(NOT CLANG_FORMAT_EXECUTABLE)
    message(FATAL_ERROR
        "clang-format is required to build this project. Install clang-format and rerun CMake.")
endif()

file(GLOB_RECURSE FORMAT_FILES CONFIGURE_DEPENDS
    "${PROJECT_SOURCE_DIR}/src/*.c"
    "${PROJECT_SOURCE_DIR}/src/*.h"
    "${PROJECT_SOURCE_DIR}/test/*.c"
    "${PROJECT_SOURCE_DIR}/test/*.h"
)
list(FILTER FORMAT_FILES EXCLUDE REGEX "/src/tools/generated_opcodes\\.h$")

add_custom_target(format
    COMMAND "${CLANG_FORMAT_EXECUTABLE}" -i ${FORMAT_FILES}
    WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
    COMMENT "Formatting C sources with clang-format"
    VERBATIM
)

add_dependencies(x64id format)
add_dependencies(x64id_disassembler format)
add_dependencies(x64id_test format)
