#include <algorithm>
#include <cctype>
#include <regex>
#include <array>
#include <cmath>
#include <set>
#include "Calculator.hpp"
#include "parser.tab.hpp"
#include "formatter.tab.hpp"
#include "user_function_dependency_locator.tab.hpp"
#include "lexer.hpp"
#include "formatter_lexer.hpp"
#include "user_function_dependency_locator_lexer.hpp"

/**
 * Creates an unordered map containing most common mathematical functions (sin, cos, etc.).
 *
 * @return Unordered map.
 */
const std::unordered_map<std::string, Function> init_func_map()
{
    std::unordered_map<std::string, Function> func_map;
    std::array<std::string, 9> func_names = { "sin", "cos", "tan", "asin", "acos", "atan", "log", "ln", "sqrt" };
    std::array<func_t, 9> functions = { sin, cos, tan, asin, acos, atan, log10, log, sqrt };
    for (int i = 0; i < func_names.size(); ++i)
    {
        Function function = { .name = func_names[i], .ptr = functions[i] };
        func_map[function.name] = function;
    }
    return func_map;
}

const std::unordered_map<std::string, Function> Calculator::function_map = init_func_map();

/**
 * Removes whitespace from a string.
 * The original string is not modified.
 * Whitespace characters are determined by the std::isspace function.
 *
 * @param str The string that whitespace is removed from.
 * @return Copy of str without any whitespace characters.
 */
std::string remove_whitespace(std::string str)
{
    str.erase(std::remove_if(str.begin(), str.end(), [](unsigned char x) { return std::isspace(x); }), str.end());
    return str;

}

Calculator::ExpressionType Calculator::identify_expression(std::string expression)
{
    // Remove any whitespace characters from the expression
    std::string modified_expression = remove_whitespace(expression);

    std::regex find_function_definition("[a-z]\\([a-z]\\)=");

    bool function_definition_found = std::regex_search(modified_expression, find_function_definition, std::regex_constants::match_continuous);

    if (function_definition_found)
    {
        return Calculator::FUNCTION_DEFINITION;
    }

    return Calculator::SOLVABLE_EXPRESSION;
}

/**
 * Locates each other UserFunction that a UserFunction depends on.
 * A UserFunction depends on another function if it is defined in terms of it, or if a dependency is defined in terms of it.
 * For example, if "f(x) = 5x + 4", "g(x) = 3 * f(x)", and "r(x) = 2^g(x)", 'r(x)' has dependencies 'f' and 'g'.
 *
 * @param user_function_map An unordered map containing each user-defined function.
 * @param expression The expression representing the UserFunction
 * @return A set containing the identifiers for each UserFunction that the expression depends on.
 */
std::unordered_set<char> Calculator::locate_user_function_dependencies(std::unordered_map<char, UserFunction>& user_function_map, std::string expression)
{
    // Remove any whitespace characters from the expression
    std::string modified_expression = remove_whitespace(expression);

    // Add marker for end of expression
    modified_expression.append("\n");

    std::unordered_set<char> dependencies;

    YY_BUFFER_STATE bs = ufdl_scan_string(modified_expression.c_str());
    ufdl_switch_to_buffer(bs);

    ufdl::parser user_function_dependency_locator(user_function_map, dependencies);
    user_function_dependency_locator();

    ufdl_delete_buffer(bs);

    return dependencies;
}

/**
 * Formats a mathematical expression to make it easier to parse.
 *
 * @param user_function_map An unordered map containing each user-defined function.
 * @param expression The expression to be formatted.
 * @return A tuple containing the formatted expression, as well as a UserFunction if the expression was a function definition.
 */
std::tuple<std::string, std::optional<UserFunction>> Calculator::format_expression(std::unordered_map<char, UserFunction>& user_function_map, std::string expression)
{
    // Create a copy of expression to modify for make it easier for the formatter to parse
    // Additionally, remove any whitespace characters from the expression
    std::string modified_expression = remove_whitespace(expression);

    // Add marker for end of expression
    modified_expression.append("\n");

    std::string formatted_expression;
    char identifier, variable;
    bool function_assignment = false;
    std::unordered_set<char> user_function_dependencies;

    YY_BUFFER_STATE bs = fmt_scan_string(modified_expression.c_str());
    fmt_switch_to_buffer(bs);

    fmt::parser formatter(user_function_map, formatted_expression, identifier, variable, function_assignment, user_function_dependencies);
    formatter();

    fmt_delete_buffer(bs);

    if (function_assignment)
    {
        return {formatted_expression, UserFunction(identifier, variable, expression, formatted_expression, user_function_dependencies)};
    }
    
    return {formatted_expression, std::nullopt};
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
