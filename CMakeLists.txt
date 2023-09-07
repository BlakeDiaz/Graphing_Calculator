cmake_minimum_required(VERSION 3.24.2)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED on)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

execute_process(COMMAND cd ${CMAKE_SOURCE_DIR})
execute_process(COMMAND flex -o src/lex.yy.cpp src/lexer.l)
execute_process(COMMAND flex -o src/formatter_lexer.yy.cpp src/formatter_lexer.l)
execute_process(COMMAND flex -o src/user_function_dependency_locator_lexer.yy.cpp src/user_function_dependency_locator_lexer.l)
execute_process(COMMAND mv lexer.hpp include)
execute_process(COMMAND mv formatter_lexer.hpp include)
execute_process(COMMAND mv user_function_dependency_locator_lexer.hpp include)
execute_process(COMMAND bison -o src/parser.tab.cpp -d src/parser.yy)
execute_process(COMMAND bison -o src/formatter.tab.cpp -d src/formatter.yy)
execute_process(COMMAND bison -o src/user_function_dependency_locator.tab.cpp -d src/user_function_dependency_locator.yy)
execute_process(COMMAND mv src/parser.tab.hpp include/parser.tab.hpp)
execute_process(COMMAND mv src/formatter.tab.hpp include/formatter.tab.hpp)
execute_process(COMMAND mv src/user_function_dependency_locator.tab.hpp include/user_function_dependency_locator.tab.hpp)
execute_process(COMMAND /usr/lib/qt6/uic forms/calculator_form.ui -o include/ui_calculator_form.hpp)

project(calc VERSION 1.0)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
find_package(OpenGL REQUIRED)
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets UiTools OpenGLWidgets)
add_executable(
    ${PROJECT_NAME}
    src/yyerror.cpp
    src/string_manipulation.cpp
    src/main.cpp
    src/input_manager.cpp
    src/calculator.cpp
    src/userfunction.cpp
    src/lex.yy.cpp
    src/formatter_lexer.yy.cpp
    src/user_function_dependency_locator_lexer.yy.cpp
    src/parser.tab.cpp
    src/formatter.tab.cpp
    src/user_function_dependency_locator.tab.cpp
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

target_link_libraries(calc PUBLIC OpenGL::GL)
target_link_libraries(calc PRIVATE Qt6::Core)
target_link_libraries(calc PRIVATE Qt6::Gui)
target_link_libraries(calc PRIVATE Qt6::Widgets)
target_link_libraries(calc PRIVATE Qt6::UiTools)
target_link_libraries(calc PRIVATE Qt6::OpenGLWidgets)

enable_testing()

add_executable(
    calculator_test
    src/yyerror.cpp
    src/string_manipulation.cpp
    src/input_manager.cpp
    src/calculator.cpp
    src/userfunction.cpp
    src/lex.yy.cpp
    src/formatter_lexer.yy.cpp
    src/user_function_dependency_locator_lexer.yy.cpp
    src/parser.tab.cpp
    src/formatter.tab.cpp
    src/user_function_dependency_locator.tab.cpp
    src/calculator_form.cpp
    src/graph_window_data.cpp
    src/axis_marker_data.cpp
    src/coordinate_transformation_data.cpp
    src/graph_widget.cpp
    include/ui_calculator_form.hpp
    include/calculator_form.hpp
    src/calculator_test.cc)
    

target_link_libraries(calculator_test PUBLIC OpenGL::GL)
target_link_libraries(calculator_test PRIVATE Qt6::Core)
target_link_libraries(calculator_test PRIVATE Qt6::Gui)
target_link_libraries(calculator_test PRIVATE Qt6::Widgets)
target_link_libraries(calculator_test PRIVATE Qt6::UiTools)
target_link_libraries(calculator_test PRIVATE Qt6::OpenGLWidgets)
target_link_libraries(calculator_test PRIVATE GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(calculator_test)

add_compile_options(export CFLAGS=-Qunused-arguments)
add_compile_options(export CPPFLAGS=-Qunused-arguments)
