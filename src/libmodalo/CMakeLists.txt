cmake_minimum_required(VERSION 3.10)
project(modalo)

add_library(modalo SHARED modalo.cpp)
target_compile_definitions(modalo PUBLIC MODALO_EXPORT) # for DLL EXPORT SYMBOLS
target_include_directories(modalo PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/includes)
target_link_libraries(modalo modbus cJSON fmt)

add_executable(testModalo main.cpp)
target_link_libraries(testModalo modalo)

add_subdirectory(libcjson)
add_subdirectory(libmodbus)
add_subdirectory(fmt)

#set(DEPLOY_DIR_MODSCAN "${CMAKE_CURRENT_BINARY_DIR}/deploy/")
#message("-- Deploying at location: ${DEPLOY_DIR_MODSCAN}")
#add_custom_command(
#    TARGET testModalo
#    POST_BUILD
#    COMMAND ${CMAKE_COMMAND} ARGS -E rm -rf ${DEPLOY_DIR_MODSCAN}
#    COMMAND ${CMAKE_COMMAND} ARGS -E make_directory ${DEPLOY_DIR_MODSCAN}
#    COMMAND ${CMAKE_COMMAND} ARGS -E copy $<TARGET_FILE:testModalo> ${DEPLOY_DIR_MODSCAN}
#    COMMAND ${CMAKE_COMMAND} ARGS -E copy $<TARGET_FILE:modalo> ${DEPLOY_DIR_MODSCAN}
#    COMMAND ${CMAKE_COMMAND} ARGS -E copy $<TARGET_FILE:modbus> ${DEPLOY_DIR_MODSCAN}
#    COMMAND ${CMAKE_COMMAND} ARGS -E copy $<TARGET_FILE:cJSON> ${DEPLOY_DIR_MODSCAN}
#    COMMAND ${CMAKE_COMMAND} ARGS -E copy $<TARGET_FILE:fmt> ${DEPLOY_DIR_MODSCAN}
#)
