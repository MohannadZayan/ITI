cmake_minimum_required(VERSION 3.16)

project(Task2 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick)

qt_standard_project_setup(REQUIRES 6.10)

# Content of downloaded design from Figma to Qt or similar
if (EXISTS "${CMAKE_CURRENT_LIST_DIR}/importedcontent/CMakeLists.txt")
    add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/importedcontent)
endif()

qt_add_executable(appTask2
    main.cpp
)

# Picks up every image dropped into images/ automatically, so new car
# photos don't require touching this file. Re-run CMake configure
# (CONFIGURE_DEPENDS) after adding new files if your build doesn't
# pick them up automatically.
file(GLOB CAR_IMAGES RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" CONFIGURE_DEPENDS
    "images/*.jpg"
    "images/*.jpeg"
    "images/*.png"
)

qt_add_qml_module(appTask2
    URI Task2

    QML_FILES
        Main.qml
        CarModel.qml
        CarDelegate.qml

    RESOURCES
        ${CAR_IMAGES}
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appTask2 PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appTask2
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appTask2
    PRIVATE Qt6::Quick
)

install(TARGETS appTask2
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
