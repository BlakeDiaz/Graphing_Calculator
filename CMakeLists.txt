cmake_minimum_required(VERSION 3.24.2)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED on)

execute_process(COMMAND cd ${CMAKE_SOURCE_DIR})
execute_process(COMMAND flex -o src/lex.yy.cpp src/lexer.l)
execute_process(COMMAND bison -o src/parser.tab.cpp -d src/parser.yy)
execute_process(COMMAND mv src/parser.tab.hpp include/parser.tab.hpp)

project(calc VERSION 1.0)
add_executable(
    ${PROJECT_NAME}
    src/main.cpp
    src/userfunction.cpp
    src/lex.yy.cpp
    src/parser.tab.cpp)
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/include)
