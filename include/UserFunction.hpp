#pragma once
#include <unordered_set>
#include <unordered_map>
#include <string>

/**
 * Class representing user-defined functions e.g. "f(x) = 5x + 3".
 */
class UserFunction
{
public:
    const char identifier; // The letter that identifies the function e.g. the "f" in "f(x) = 5x + 3".
    const char variable; // The variable that the function uses e.g. the "x" in "f(x) = 5x + 3".
    const std::string expression; // The text form of the function e.g. "f(x) = 5x + 3".
    std::string formatted_expression; // The body of the function formatted to make it easier to parse e.g. "5*x+3" from the expression "f(x) = 5x + 3". Composite functions are also simplified in this form.
    std::unordered_set<char> user_function_dependencies; // The UserFunctions that the function is defined in terms of e.g. "g(x)" in "f(x) = 5x + 3g(x)".

    static char find_identifier(std::string expression);
    static char find_variable(std::string expression);

    UserFunction(std::unordered_map<char, UserFunction> user_function_map, std::string expression);
    UserFunction(std::string expression, std::string formatted_expression, std::unordered_set<char> user_function_dependencies);
    UserFunction(const char identifier, const char variable, const std::string expression, std::string formatted_expression, std::unordered_set<char> user_function_dependencies);
    std::string call(const std::string argument);
};
