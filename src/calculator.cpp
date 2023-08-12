#include <optional>
#include <array>
#include <cmath>
#include "Calculator.hpp"
#include "parser.tab.hpp"
#include "formatter.tab.hpp"
#include "lexer.hpp"
#include "formatter_lexer.hpp"

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
 * Formats a mathematical expression to make it easier to parse.
 *
 * @param user_function_map An unordered map containing each user-defined function.
 * @param expression The expression to be formatted.
 * @return A tuple containing the formatted expression, as well as a UserFunction if the expression was a function definition.
 */
std::tuple<std::string, std::optional<UserFunction>> Calculator::format_expression(std::unordered_map<char, UserFunction>& user_function_map, std::string expression)
{
    std::string formatted_expression;
    char identifier, variable;
    bool function_assignment = false;

    YY_BUFFER_STATE bs = fmt_scan_string(expression.c_str());
    fmt_switch_to_buffer(bs);

    fmt::parser formatter(user_function_map, formatted_expression, identifier, variable, function_assignment);
    formatter();

    fmt_delete_buffer(bs);

    if (function_assignment)
    {
        return {formatted_expression, UserFunction(identifier, variable, expression, formatted_expression)};
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
    double result;
    
    YY_BUFFER_STATE bs = yy_scan_string(expression.c_str());
    yy_switch_to_buffer(bs);

    yy::parser parser(Calculator::function_map, result);
    parser();

    yy_delete_buffer(bs);

    return result;
}
