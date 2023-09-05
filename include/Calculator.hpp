#pragma once
#include <unordered_map>
#include <optional>
#include <string>
#include <tuple>
#include "Function.hpp"
#include "User_Function.hpp"

/**
 * Container class for the formatter and computation parsers.
 */
class Calculator
{
public:
    enum ExpressionType { SOLVABLE_EXPRESSION, FUNCTION_DEFINITION };

    const static std::unordered_map<std::string, Function> function_map;    // Contains functions like sin, cos, etc.
    
    static ExpressionType identify_expression(std::string expression);
    static std::unordered_set<char> locate_user_function_dependencies(std::unordered_map<char, User_Function>& user_function_map, std::string expression);
    static std::string format_expression(std::unordered_map<char, User_Function>& user_function_map, std::string expression);
    static double solve_expression(std::string formatted_expression);
};
