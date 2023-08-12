#pragma once
#include <optional>
#include <string>
#include <tuple>
#include <unordered_map>
#include <map>
#include "Function.hpp"
#include "UserFunction.hpp"

/**
 * Container class for the formatter and computation parsers.
 */
class Calculator
{
public:
    const static std::unordered_map<std::string, Function> function_map;    // Contains functions like sin, cos, etc.
    static std::unordered_map<char, UserFunction> user_function_map;    // Stores user-defined functions

    
    static std::tuple<std::string, std::optional<UserFunction>> format_expression(std::unordered_map<char, UserFunction>& user_function_map, std::string expression);
    static double solve_expression(std::string formatted_expression);

};
