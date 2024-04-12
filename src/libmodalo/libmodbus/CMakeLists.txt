cmake_minimum_required(VERSION 3.10)
project(modbus)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/includes)
add_library(modbus SHARED
            modbus.c
            modbus-tcp.c
            modbus-rtu.c
            modbus-data.c)
target_link_libraries(modbus ws2_32)
target_compile_definitions(modbus PUBLIC DLLBUILD)