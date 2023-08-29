cmake_minimum_required(VERSION 3.24.2)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED on)

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

project(calc VERSION 1.0)
add_executable(
    ${PROJECT_NAME}
    src/yyerror.cpp
    src/string_manipulation.cpp
    src/main.cpp
    src/calculator.cpp
    src/userfunction.cpp
    src/lex.yy.cpp
    src/formatter_lexer.yy.cpp
    src/user_function_dependency_locator_lexer.yy.cpp
    src/parser.tab.cpp
    src/formatter.tab.cpp
    src/user_function_dependency_locator.tab.cpp)
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/include)

enable_testing()

add_executable(
    calculator_test
    src/yyerror.cpp
    src/string_manipulation.cpp
    src/calculator.cpp
    src/userfunction.cpp
    src/lex.yy.cpp
    src/formatter_lexer.yy.cpp
    src/user_function_dependency_locator_lexer.yy.cpp
    src/parser.tab.cpp
    src/formatter.tab.cpp
    src/user_function_dependency_locator.tab.cpp
    src/calculator_test.cc)
    

target_link_libraries(
    calculator_test
    GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(calculator_test)
