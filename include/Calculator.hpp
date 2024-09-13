#pragma once
#include "Function.hpp"
#include "User_Function.hpp"
#include <optional>
#include <string>
#include <tuple>
#include <unordered_map>

/**
 * Container class for the formatter and computation parsers.
 */
class Calculator
{
  public:
    enum ExpressionType
    {
        SOLVABLE_EXPRESSION,
        FUNCTION_DEFINITION
    };

    const static std::unordered_map<std::string, Function> function_map; // Contains functions like sin, cos, etc.

    static ExpressionType identify_expression(std::string expression);
    static std::unordered_set<char> locate_user_function_dependencies(const std::string& expression, int line_number = 1);
    static std::string format_expression(std::unordered_map<char, User_Function>& user_function_map,
                                         std::string expression, int line_number = 1);
    static double solve_expression(std::string formatted_expression);
};
