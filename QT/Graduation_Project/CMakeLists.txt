cmake_minimum_required(VERSION 3.16)

project(Graduation_Project VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick)

qt_standard_project_setup(REQUIRES 6.10)

# Content of downloaded design from Figma to Qt or similar
if (EXISTS "${CMAKE_CURRENT_LIST_DIR}/importedcontent/CMakeLists.txt")
    add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/importedcontent)
endif()

qt_add_executable(appGraduation_Project
    src/main.cpp
)

target_include_directories(appGraduation_Project
    PRIVATE include
)

qt_add_qml_module(appGraduation_Project
    URI Graduation_Project
    QML_FILES
        Main.qml
        SOURCES include/mediamode.h src/mediamode.cpp
        SOURCES include/player.h src/player.cpp
        SOURCES include/audioplayer.h src/audioplayer.cpp
        SOURCES include/videoplayer.h src/videoplayer.cpp
        SOURCES include/mediacontroller.h src/mediacontroller.cpp
        SOURCES include/bluetoothmanager.h src/bluetoothmanager.cpp
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appGraduation_Project PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appGraduation_Project
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appGraduation_Project
    PRIVATE Qt6::Quick
)

install(TARGETS appGraduation_Project
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
