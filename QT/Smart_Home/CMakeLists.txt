cmake_minimum_required(VERSION 3.16)

project(Smart_Home VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick)

qt_standard_project_setup(REQUIRES 6.10)

# Content of downloaded design from Figma to Qt or similar
if (EXISTS "${CMAKE_CURRENT_LIST_DIR}/importedcontent/CMakeLists.txt")
    add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/importedcontent)
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

        RESOURCES
            Images/logo.png
            Images/light.png
            Images/light_bed.png
            Images/fan_2.jpeg
            Images/images.png
            Images/garage_2.jpeg
            Images/Light-bulb.png
            QML_FILES settingsPage.qml

)
# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appSmart_Home PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appSmart_Home
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appSmart_Home
    PRIVATE Qt6::Quick
)

install(TARGETS appSmart_Home
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
