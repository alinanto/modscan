cmake_minimum_required(VERSION 3.10)
project(cJSON)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/includes)
add_library(cJSON SHARED cJSON.c)