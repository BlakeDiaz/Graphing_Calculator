#pragma once
#include "Function.hpp"
#include "User_Function.hpp"
#include <optional>
#include <string>
#include <tuple>
#include <unordered_map>
#include <Parse_Error.hpp>

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
    static std::tuple<std::unordered_set<char>, Parse_Error> locate_user_function_dependencies(const std::string& expression, int line_number = 1);
    static std::tuple<std::string, Parse_Error> format_expression(std::unordered_map<char, User_Function>& user_function_map,
                                         std::string expression, int line_number = 1);
    static std::tuple<double, Parse_Error> solve_expression(std::string formatted_expression, int line_number = 1);
};
