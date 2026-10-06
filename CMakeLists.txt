cmake_minimum_required(VERSION 3.16)

project(ui-app VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

qt_standard_project_setup()

qt_add_executable(ui-app
    Window.cpp
    LoaderWidget.cpp
    ClockWidget.cpp
    Main.cpp
)

target_link_libraries(ui-app PRIVATE Qt6::Widgets)

set_target_properties(ui-app PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
)