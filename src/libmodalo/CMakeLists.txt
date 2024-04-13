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


set(DEPLOY_DIR_MODSCAN "${CMAKE_CURRENT_BINARY_DIR}/deploy/")
message("-- Deploying at location: ${DEPLOY_DIR_MODSCAN}")
add_custom_command(
    TARGET testModalo
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} ARGS -E rm -rf ${DEPLOY_DIR_MODSCAN}
    COMMAND ${CMAKE_COMMAND} ARGS -E make_directory ${DEPLOY_DIR_MODSCAN}
    COMMAND ${CMAKE_COMMAND} ARGS -E copy $<TARGET_FILE:testModalo> ${DEPLOY_DIR_MODSCAN}
    COMMAND ${CMAKE_COMMAND} ARGS -E copy $<TARGET_FILE:modalo> ${DEPLOY_DIR_MODSCAN}
    COMMAND ${CMAKE_COMMAND} ARGS -E copy "libmodbus/libmodbus.dll" ${DEPLOY_DIR_MODSCAN}
    COMMAND ${CMAKE_COMMAND} ARGS -E copy "libcjson/libcJSON.dll" ${DEPLOY_DIR_MODSCAN}
)
