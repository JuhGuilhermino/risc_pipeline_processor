cmake_minimum_required(VERSION 3.10)
project(risc_pipeline_processor)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 🔧 Ajuste para o caminho do seu SystemC
set(SYSTEMC_HOME /usr/local/systemc-3.0.2)

# Includes
include_directories(
    ${SYSTEMC_HOME}/include
    ${CMAKE_SOURCE_DIR}/src
)

# Libs
link_directories(
    ${SYSTEMC_HOME}/lib-linux64
)

add_executable(test_alu
    src/components/alu/alu_tb.cpp
    src/components/alu/alu.cpp
)

add_executable(test_reg
    src/components/registers/registers_tb.cpp
    src/components/registers/registers.cpp
)

add_executable(test_imem
    src/components/instruction_memory/instruction_memory_tb.cpp
    src/components/instruction_memory/instruction_memory.cpp
)

add_executable(test_dmem
    src/components/data_memory/data_memory_tb.cpp
    src/components/data_memory/data_memory.cpp
)

target_link_libraries(test_alu systemc)
target_link_libraries(test_reg systemc)
target_link_libraries(test_imem systemc)
target_link_libraries(test_dmem systemc)