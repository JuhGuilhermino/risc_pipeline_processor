cmake_minimum_required(VERSION 3.10)
project(risc_pipeline_processor)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SYSTEMC_HOME /usr/local/systemc-3.0.2)

include_directories(
    ${SYSTEMC_HOME}/include
    ${CMAKE_SOURCE_DIR}/src
)

link_directories(
    ${SYSTEMC_HOME}/lib
)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-rpath,${SYSTEMC_HOME}/lib")

add_executable(test_alu
    src/components/alu/alu_tb.cpp
    src/components/alu/alu.cpp
)

add_executable(test_reg
    src/components/registers/registers_tb.cpp
    src/components/registers/registers.cpp
)

add_executable(test_pc
    src/components/pc/pc_tb.cpp
    src/components/pc/pc.cpp
)

add_executable(test_mux
    src/components/mux/mux_tb.cpp
    src/components/mux/mux.cpp
)

add_executable(test_sign_extend
    src/components/sign_extend/sign_extend_tb.cpp
    src/components/sign_extend/sign_extend.cpp
)

add_executable(test_unit_control
    src/control/unit_control_tb.cpp
    src/control/unit_control.cpp
)

add_executable(test_datapath
    src/datapath/datapath_tb.cpp
    src/datapath/datapath.cpp

    src/components/alu/alu.cpp
    src/components/mux/mux.cpp
    src/components/sign_extend/sign_extend.cpp
    src/components/registers/registers.cpp
    src/control/unit_control.cpp
)

add_executable(test_processor
    src/processor/processor_tb.cpp
    src/processor/processor.cpp

    src/datapath/datapath.cpp

    src/components/alu/alu.cpp
    src/components/mux/mux.cpp
    src/components/sign_extend/sign_extend.cpp
    src/components/registers/registers.cpp

    src/control/unit_control.cpp
)

target_link_libraries(test_alu systemc)
target_link_libraries(test_reg systemc)
target_link_libraries(test_pc systemc)
target_link_libraries(test_mux systemc)
target_link_libraries(test_sign_extend systemc)
target_link_libraries(test_unit_control systemc)
target_link_libraries(test_datapath systemc)
target_link_libraries(test_processor systemc)

