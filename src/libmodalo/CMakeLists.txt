cmake_minimum_required(VERSION 3.10)
project(modalo)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/includes)

add_library(modalo SHARED modalo.cpp)
target_compile_definitions(modalo PUBLIC MODALO_EXPORT) # for DLL EXPORT SYMBOLS

add_executable(testModalo main.cpp)
target_link_libraries(testModalo modalo)