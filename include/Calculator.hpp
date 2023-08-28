#pragma once
#include <unordered_map>
#include <optional>
#include <string>
#include <tuple>
#include "Function.hpp"
#include "UserFunction.hpp"

/**
 * Container class for the formatter and computation parsers.
 */
class Calculator
{
public:
    enum ExpressionType { SOLVABLE_EXPRESSION, FUNCTION_DEFINITION };

    const static std::unordered_map<std::string, Function> function_map;    // Contains functions like sin, cos, etc.
    
    static ExpressionType identify_expression(std::string expression);
    static std::tuple<std::string, std::optional<UserFunction>> format_expression(std::unordered_map<char, UserFunction>& user_function_map, std::string expression);
    static double solve_expression(std::string formatted_expression);
};
