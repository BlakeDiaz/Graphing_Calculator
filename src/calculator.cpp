#include "Calculator.hpp"
#include "formatter.tab.hpp"
#include "formatter_lexer.hpp"
#include "lexer.hpp"
#include "parser.tab.hpp"
#include "string_manipulation.hpp"
#include "user_function_dependency_locator.tab.hpp"
#include "user_function_dependency_locator_lexer.hpp"
#include <algorithm>
#include <array>
#include <cctype>
#include <cmath>
#include <regex>
#include <set>

/**
 * Creates an unordered map containing most common mathematical functions (sin, cos, etc.).
 *
 * @return Unordered map.
 */
const std::unordered_map<std::string, Function> init_func_map()
{
    std::unordered_map<std::string, Function> func_map;
    std::array<std::string, 9> func_names = {"sin", "cos", "tan", "asin", "acos", "atan", "log", "ln", "sqrt"};
    std::array<func_t, 9> functions = {sin, cos, tan, asin, acos, atan, log10, log, sqrt};
    for (int i = 0; i < func_names.size(); ++i)
    {
        Function function = {.name = func_names[i], .ptr = functions[i]};
        func_map[function.name] = function;
    }
    return func_map;
}

const std::unordered_map<std::string, Function> Calculator::function_map = init_func_map();

Calculator::ExpressionType Calculator::identify_expression(std::string expression)
{
    // Remove any whitespace characters from the expression
    std::string modified_expression = remove_whitespace(expression);

    std::regex find_function_definition("[a-z]\\([a-z]\\)=");

    bool function_definition_found =
        std::regex_search(modified_expression, find_function_definition, std::regex_constants::match_continuous);

    if (function_definition_found)
    {
        return Calculator::FUNCTION_DEFINITION;
    }

    return Calculator::SOLVABLE_EXPRESSION;
}

/**
 * Locates each User_Function that a User_Function directly depends on.
 * A User_Function directly depends on another function if it is directly defined in terms of it.
 * For example, if "f(x) = 5x + 4", "g(x) = 3 * f(x)", and "r(x) = 2^g(x)", 'r(x)' has direct dependency 'g', and
 * indirect dependency 'f'.
 *
 * @param user_function_map An unordered map containing each user-defined function.
 * @param expression The expression representing the User_Function
 * @return A set containing the identifiers for each User_Function that the expression depends on.
 */
std::unordered_set<char> Calculator::locate_user_function_dependencies(std::string expression)
{
    // Remove any whitespace characters from the expression
    std::string modified_expression = remove_whitespace(expression);

    // Add marker for end of expression
    modified_expression.append("\n");

    std::unordered_set<char> dependencies;

    YY_BUFFER_STATE bs = ufdl_scan_string(modified_expression.c_str());
    ufdl_switch_to_buffer(bs);

    ufdl::parser user_function_dependency_locator(dependencies, User_Function::find_variable(expression));
    user_function_dependency_locator();

    ufdl_delete_buffer(bs);

    return dependencies;
}

/**
 * Formats a mathematical expression to make it easier to parse.
 *
 * @param user_function_map An unordered map containing each user-defined function.
 * @param expression The expression to be formatted.
 * @return A tuple containing the formatted expression, as well as a User_Function if the expression was a function
 * definition.
 */
std::string Calculator::format_expression(std::unordered_map<char, User_Function>& user_function_map,
                                          std::string expression)
{
    // Create a copy of expression to modify for make it easier for the formatter to parse
    // Additionally, remove any whitespace characters from the expression
    std::string modified_expression = remove_whitespace(expression);

    // Add marker for end of expression
    modified_expression.append("\n");

    std::string formatted_expression;

    YY_BUFFER_STATE bs = fmt_scan_string(modified_expression.c_str());
    fmt_switch_to_buffer(bs);

    fmt::parser formatter(user_function_map, formatted_expression);
    formatter();

    fmt_delete_buffer(bs);

    return formatted_expression;
}

/**
 * Computes the solution to a formatted mathematical expression.
 * For example, passing "5*3+4" would return 19.
 *
 * @param expression The formatted expression to be computed.
 * @return The solution to the expression.
 */
double Calculator::solve_expression(std::string expression)
{
    // Create a copy of expression to modify for make it easier for the computation parser to parse
    std::string modified_expression = expression;

    // Add marker for end of expression
    modified_expression.append("\n");

    double result;

    YY_BUFFER_STATE bs = yy_scan_string(modified_expression.c_str());
    yy_switch_to_buffer(bs);

    yy::parser parser(Calculator::function_map, result);
    parser();

    yy_delete_buffer(bs);

    return result;
}
