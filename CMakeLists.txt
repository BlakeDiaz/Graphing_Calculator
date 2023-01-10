cmake_minimum_required(VERSION 3.24.2)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED on)

execute_process(COMMAND cd ${CMAKE_SOURCE_DIR})
execute_process(COMMAND flex -o src/lex.yy.cpp src/calc.ll)
execute_process(COMMAND bison -o src/calc.tab.cpp -d src/calc.yy)
execute_process(COMMAND mv src/calc.tab.hpp include/calc.tab.hpp)

project(calc VERSION 1.0)
add_executable(
    ${PROJECT_NAME}
    src/calc.cpp
    src/userfunction.cpp
    src/lex.yy.cpp
    src/calc.tab.cpp)
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/include)
