# SPDX-License-Identifier: GPL-2.0-only

if(NOT BUILD_TESTING)
	return()
endif()

add_executable(x64id_test
	main_test.c
)
target_link_libraries(x64id_test PRIVATE x64id_decoder)
x64id_configure_target(x64id_test)

find_package(Python3 COMPONENTS Interpreter REQUIRED)

add_test(
	NAME disassembler_opcode_coverage
	COMMAND "${Python3_EXECUTABLE}"
		"${CMAKE_CURRENT_SOURCE_DIR}/test_disassembler.py"
		"$<TARGET_FILE:x64id_disassembler>"
		"${PROJECT_SOURCE_DIR}/src/tools/definitions.txt"
)

add_executable(function_length_test
	function_length_test.c
	${PROJECT_SOURCE_DIR}/src/utils/function_length.c
	${PROJECT_SOURCE_DIR}/src/queue.c
	${PROJECT_SOURCE_DIR}/src/vector.c
)
target_link_libraries(function_length_test PRIVATE x64id_decoder)
x64id_configure_target(function_length_test)

add_test(
	NAME function_length_control_flow
	COMMAND "$<TARGET_FILE:function_length_test>"
)
