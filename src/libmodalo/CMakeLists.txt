cmake_minimum_required(VERSION 3.10)
project(modalo)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/includes)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/libmodbus/includes)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/libcjson/includes)

add_library(modalo SHARED modalo.cpp)
target_compile_definitions(modalo PUBLIC MODALO_EXPORT) # for DLL EXPORT SYMBOLS

add_executable(testModalo main.cpp)
target_link_libraries(modalo modbus cJSON)
target_link_libraries(testModalo modalo)

add_subdirectory(libcjson)
add_subdirectory(libmodbus)