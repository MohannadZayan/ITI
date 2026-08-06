cmake_minimum_required(VERSION 3.16)

project(Smart_Home VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick)

qt_standard_project_setup(REQUIRES 6.10)

# Include imported content if it exists
if(EXISTS "${CMAKE_CURRENT_LIST_DIR}/importedcontent/CMakeLists.txt")
    add_subdirectory(importedcontent)
endif()

qt_add_executable(appSmart_Home
    main.cpp
)

qt_add_qml_module(appSmart_Home
    URI Smart_Home

    QML_FILES
        Main.qml
        LoginPage.qml
        DashboardPage.qml
        settingsPage.qml
        DeviceCard.qml

    RESOURCES
        Images/logo.png
        Images/light.png
        Images/light_bed.png
        Images/fan_2.jpeg
        Images/images.png
        Images/garage_2.jpeg
        Images/Light-bulb.png
)

set_target_properties(appSmart_Home PROPERTIES
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

target_link_libraries(appSmart_Home
    PRIVATE Qt6::Quick
)

install(TARGETS appSmart_Home
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)