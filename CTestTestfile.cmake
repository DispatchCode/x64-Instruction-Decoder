# CMake generated Testfile for 
# Source directory: /home/user/Documenti/x64-Instruction-Decoder
# Build directory: /home/user/Documenti/x64-Instruction-Decoder
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(disassembler_opcode_coverage "/usr/bin/python3.13" "/home/user/Documenti/x64-Instruction-Decoder/test_disassembler.py" "/home/user/Documenti/x64-Instruction-Decoder/x64id_disassembler" "/home/user/Documenti/x64-Instruction-Decoder/src/tools/definitions.txt")
set_tests_properties(disassembler_opcode_coverage PROPERTIES  _BACKTRACE_TRIPLES "/home/user/Documenti/x64-Instruction-Decoder/test/CMakeLists.txt;7;add_test;/home/user/Documenti/x64-Instruction-Decoder/test/CMakeLists.txt;0;;/home/user/Documenti/x64-Instruction-Decoder/CMakeLists.txt;14;include;/home/user/Documenti/x64-Instruction-Decoder/CMakeLists.txt;0;")
