# SPDX-License-Identifier: GPL-2.0-only

cmake_minimum_required(VERSION 3.16)
project(x64id LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(X64ID_DECODER_SOURCES
	${PROJECT_SOURCE_DIR}/src/x64id.c
	${PROJECT_SOURCE_DIR}/src/disasm.c
)

set(X64ID_ANALYSIS_SOURCES
	${PROJECT_SOURCE_DIR}/src/utils/function_length.c
	${PROJECT_SOURCE_DIR}/src/vector.c
	${PROJECT_SOURCE_DIR}/src/queue.c
)

set(X64ID_SAMPLE_SOURCES
	${PROJECT_SOURCE_DIR}/src/utils/test_functions.c
)

add_library(x64id_decoder STATIC
	${X64ID_DECODER_SOURCES}
)
target_include_directories(x64id_decoder PUBLIC
	${PROJECT_SOURCE_DIR}/src
)

add_executable(x64id
	${X64ID_ANALYSIS_SOURCES}
	${X64ID_SAMPLE_SOURCES}
	${PROJECT_SOURCE_DIR}/src/main.c
)
target_link_libraries(x64id PRIVATE x64id_decoder)

add_executable(x64id_disassembler
	${PROJECT_SOURCE_DIR}/src/main_disassembler.c
	${PROJECT_SOURCE_DIR}/src/disassembler.c
	${PROJECT_SOURCE_DIR}/src/disassembler_output.c
)
target_link_libraries(x64id_disassembler PRIVATE x64id_decoder)

# Prefer an unversioned clang-format, then fall back to the newest versioned
# binary available in PATH (for example clang-format-22).
find_program(CLANG_FORMAT_EXECUTABLE NAMES clang-format)
if(NOT CLANG_FORMAT_EXECUTABLE AND UNIX)
	string(REPLACE ":" ";" CLANG_FORMAT_PATH_DIRS "$ENV{PATH}")
	set(CLANG_FORMAT_CANDIDATES)
	foreach(PATH_DIR IN LISTS CLANG_FORMAT_PATH_DIRS)
		file(GLOB PATH_CANDIDATES "${PATH_DIR}/clang-format-[0-9]*")
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
		"clang-format is required. Install it and rerun CMake.")
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

function(x64id_configure_target TARGET_NAME)
	if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
		target_compile_options(${TARGET_NAME} PRIVATE -O2)
	endif()
	add_dependencies(${TARGET_NAME} format)
endfunction()

x64id_configure_target(x64id)
x64id_configure_target(x64id_disassembler)
x64id_configure_target(x64id_decoder)

include(CTest)
add_subdirectory(test)
