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
#[[ Calculator ]]#
add_custom_command(
        OUTPUT
            ${CMAKE_SOURCE_DIR}/src/parser.tab.cpp
            ${CMAKE_SOURCE_DIR}/include/parser.tab.hpp
        COMMAND
            bison -o ${CMAKE_SOURCE_DIR}/src/parser.tab.cpp -d ${CMAKE_SOURCE_DIR}/src/parser.yy && mv ${CMAKE_SOURCE_DIR}/src/parser.tab.hpp ${CMAKE_SOURCE_DIR}/include
        DEPENDS
            ${CMAKE_SOURCE_DIR}/src/parser.yy
        VERBATIM
)
add_custom_command(
        OUTPUT
            ${CMAKE_SOURCE_DIR}/src/lex.yy.cpp
            ${CMAKE_SOURCE_DIR}/include/lexer.hpp
        COMMAND
            flex -o ${CMAKE_SOURCE_DIR}/src/lex.yy.cpp ${CMAKE_SOURCE_DIR}/src/lexer.l && mv lexer.hpp ${CMAKE_SOURCE_DIR}/include
        DEPENDS
            ${CMAKE_SOURCE_DIR}/src/lexer.l
        VERBATIM
)
#[[ Formatter ]]#
add_custom_command(
        OUTPUT
            ${CMAKE_SOURCE_DIR}/src/formatter.tab.cpp
            ${CMAKE_SOURCE_DIR}/include/formatter.tab.hpp
        COMMAND
            bison -o ${CMAKE_SOURCE_DIR}/src/formatter.tab.cpp -d ${CMAKE_SOURCE_DIR}/src/formatter.yy && mv ${CMAKE_SOURCE_DIR}/src/formatter.tab.hpp ${CMAKE_SOURCE_DIR}/include
        DEPENDS
            ${CMAKE_SOURCE_DIR}/src/formatter.yy
        VERBATIM
)
add_custom_command(
        OUTPUT
            ${CMAKE_SOURCE_DIR}/src/formatter_lexer.yy.cpp
            ${CMAKE_SOURCE_DIR}/include/formatter_lexer.hpp
        COMMAND
            flex -o ${CMAKE_SOURCE_DIR}/src/formatter_lexer.yy.cpp ${CMAKE_SOURCE_DIR}/src/formatter_lexer.l && mv formatter_lexer.hpp ${CMAKE_SOURCE_DIR}/include
        DEPENDS
            ${CMAKE_SOURCE_DIR}/src/formatter_lexer.l
        VERBATIM
)
#[[ User Function Dependency Locator]]#
add_custom_command(
        OUTPUT
            ${CMAKE_SOURCE_DIR}/src/user_function_dependency_locator.tab.cpp
            ${CMAKE_SOURCE_DIR}/include/user_function_dependency_locator.tab.hpp
        COMMAND
            bison -o ${CMAKE_SOURCE_DIR}/src/user_function_dependency_locator.tab.cpp -d ${CMAKE_SOURCE_DIR}/src/user_function_dependency_locator.yy && mv ${CMAKE_SOURCE_DIR}/src/user_function_dependency_locator.tab.hpp ${CMAKE_SOURCE_DIR}/include
        DEPENDS
            ${CMAKE_SOURCE_DIR}/src/user_function_dependency_locator.yy
        VERBATIM
)
add_custom_command(
        OUTPUT
            ${CMAKE_SOURCE_DIR}/src/user_function_dependency_locator_lexer.yy.cpp
            ${CMAKE_SOURCE_DIR}/include/user_function_dependency_locator_lexer.hpp
        COMMAND
            flex -o ${CMAKE_SOURCE_DIR}/src/user_function_dependency_locator_lexer.yy.cpp ${CMAKE_SOURCE_DIR}/src/user_function_dependency_locator_lexer.l && mv user_function_dependency_locator_lexer.hpp ${CMAKE_SOURCE_DIR}/include
        DEPENDS
            ${CMAKE_SOURCE_DIR}/src/user_function_dependency_locator_lexer.l
        VERBATIM
)

project(calc VERSION 1.0)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_SOURCE_DIR}/forms)
find_package(OpenGL REQUIRED)
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets UiTools OpenGLWidgets)
qt_add_executable(
    ${PROJECT_NAME}
    ${CMAKE_SOURCE_DIR}/forms/calculator_form.ui
    ${CMAKE_SOURCE_DIR}/src/yyerror.cpp
    ${CMAKE_SOURCE_DIR}/src/string_manipulation.cpp
    ${CMAKE_SOURCE_DIR}/src/main.cpp
    ${CMAKE_SOURCE_DIR}/src/input_manager.cpp
    ${CMAKE_SOURCE_DIR}/src/calculator.cpp
    ${CMAKE_SOURCE_DIR}/src/userfunction.cpp
    ${CMAKE_SOURCE_DIR}/src/lex.yy.cpp
    ${CMAKE_SOURCE_DIR}/src/formatter_lexer.yy.cpp
    ${CMAKE_SOURCE_DIR}/src/user_function_dependency_locator_lexer.yy.cpp
    ${CMAKE_SOURCE_DIR}/src/parser.tab.cpp
    ${CMAKE_SOURCE_DIR}/src/formatter.tab.cpp
    ${CMAKE_SOURCE_DIR}/src/user_function_dependency_locator.tab.cpp
    ${CMAKE_SOURCE_DIR}/src/calculator_form.cpp
    ${CMAKE_SOURCE_DIR}/src/graph_window_data.cpp
    ${CMAKE_SOURCE_DIR}/src/axis_marker_data.cpp
    ${CMAKE_SOURCE_DIR}/src/coordinate_transformation_data.cpp
    ${CMAKE_SOURCE_DIR}/src/graph_widget.cpp
    ${CMAKE_SOURCE_DIR}/src/parse_error.cpp
    ${CMAKE_SOURCE_DIR}/include/calculator_form.hpp)
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
    ${CMAKE_SOURCE_DIR}/src/yyerror.cpp
    ${CMAKE_SOURCE_DIR}/src/string_manipulation.cpp
    ${CMAKE_SOURCE_DIR}/src/input_manager.cpp
    ${CMAKE_SOURCE_DIR}/src/calculator.cpp
    ${CMAKE_SOURCE_DIR}/src/userfunction.cpp
    ${CMAKE_SOURCE_DIR}/src/lex.yy.cpp
    ${CMAKE_SOURCE_DIR}/src/formatter_lexer.yy.cpp
    ${CMAKE_SOURCE_DIR}/src/user_function_dependency_locator_lexer.yy.cpp
    ${CMAKE_SOURCE_DIR}/src/parser.tab.cpp
    ${CMAKE_SOURCE_DIR}/src/formatter.tab.cpp
    ${CMAKE_SOURCE_DIR}/src/user_function_dependency_locator.tab.cpp
    ${CMAKE_SOURCE_DIR}/src/calculator_form.cpp
    ${CMAKE_SOURCE_DIR}/src/graph_window_data.cpp
    ${CMAKE_SOURCE_DIR}/src/axis_marker_data.cpp
    ${CMAKE_SOURCE_DIR}/src/coordinate_transformation_data.cpp
    ${CMAKE_SOURCE_DIR}/src/graph_widget.cpp
    ${CMAKE_SOURCE_DIR}/src/parse_error.cpp
    ${CMAKE_SOURCE_DIR}/include/calculator_form.hpp
    ${CMAKE_SOURCE_DIR}/src/calculator_test.cc)
    

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
