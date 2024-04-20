cmake_minimum_required(VERSION 3.5)

message("-- Source Directory: ${CMAKE_CURRENT_SOURCE_DIR}")
message("-- Cmake Prefix Path: ${CMAKE_PREFIX_PATH}")
message("-- Build Directory: ${CMAKE_CURRENT_BINARY_DIR}")

project(modscan VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(DEPLOY_DIR_MODSCAN "${CMAKE_CURRENT_BINARY_DIR}/../bin/")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${DEPLOY_DIR_MODSCAN})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(modscan
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET modscan APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(modscan SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(modscan
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(modscan PRIVATE Qt${QT_VERSION_MAJOR}::Widgets modalo)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.modscan)
endif()
set_target_properties(modscan PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS modscan
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(modscan)
endif()

IF (WIN32)
    find_program(QT_DEPLOY_COMMAND windeployqt CMAKE_PREFIX_PATH)
    message("-- Found windeployqt.exe at location: ${QT_DEPLOY_COMMAND}")
    message("-- Deploying at location: ${DEPLOY_DIR_MODSCAN}")
    add_custom_command(
        TARGET modscan
        POST_BUILD
        #COMMAND ${CMAKE_COMMAND} ARGS -E rm -rf ${DEPLOY_DIR_MODSCAN}
        #COMMAND ${CMAKE_COMMAND} ARGS -E make_directory ${DEPLOY_DIR_MODSCAN}
        #COMMAND ${CMAKE_COMMAND} ARGS -E copy $<TARGET_FILE:modscan> ${DEPLOY_DIR_MODSCAN}
        COMMAND ${QT_DEPLOY_COMMAND} ARGS ${DEPLOY_DIR_MODSCAN}\$<TARGET_FILE_NAME:modscan>
    )
ELSE()
  # Set stuff for other systems
ENDIF()

add_subdirectory(libmodalo)