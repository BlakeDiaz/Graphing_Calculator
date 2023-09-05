cmake_minimum_required(VERSION 3.24.2)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED on)

execute_process(COMMAND cd ${CMAKE_SOURCE_DIR})
execute_process(COMMAND /usr/lib/qt6/uic forms/calculator_form.ui -o include/ui_calculator_form.hpp)

project(program VERSION 1.0)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets UiTools OpenGLWidgets)
add_executable(
    ${PROJECT_NAME}
    src/main.cpp
    src/calculator_form.cpp
    src/graph_window_data.cpp
    src/axis_marker_data.cpp
    src/coordinate_transformation_data.cpp
    src/graph_widget.cpp
    include/ui_calculator_form.hpp
    include/calculator_form.hpp)
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(program PUBLIC glfw)
target_link_libraries(program PUBLIC OpenGL::GL)
target_link_libraries(program PRIVATE Qt6::Core)
target_link_libraries(program PRIVATE Qt6::Gui)
target_link_libraries(program PRIVATE Qt6::Widgets)
target_link_libraries(program PRIVATE Qt6::UiTools)
target_link_libraries(program PRIVATE Qt6::OpenGLWidgets)
add_compile_options(export CFLAGS=-Qunused-arguments)
add_compile_options(export CPPFLAGS=-Qunused-arguments)
