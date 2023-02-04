#pragma once
#include <string>
#include <map>
#include "Function.hpp"
#include "UserFunction.hpp"

class Calculator
{
public:
    const static std::unordered_map<std::string, Function> function_map;          // Contains functions like sin, cos, etc.
    static std::unordered_map<char, UserFunction> user_function_map;    // Stores user-defined functions

    static std::string format_expression(std::string expression);              // Formattes expression for easier parsing
    static double solve_expression(std::string formatted_expression);          // Takes in formatted expression, returns answer
    
};
