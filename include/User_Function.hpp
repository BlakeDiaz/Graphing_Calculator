#pragma once
#include <QColor>
#include <string>
#include <unordered_map>
#include <unordered_set>

/**
 * Class representing user-defined functions e.g. "f(x) = 5x + 3".
 */
class User_Function
{
  public:
    const char identifier;        // The letter that identifies the function e.g. the "f" in "f(x) = 5x + 3".
    const char variable;          // The variable that the function uses e.g. the "x" in "f(x) = 5x + 3".
    const std::string expression; // The text form of the function e.g. "f(x) = 5x + 3".
    const std::string
        formatted_expression; // The body of the function formatted to make it easier to parse e.g. "5*x+3" from the
                              // expression "f(x) = 5x + 3". Composite functions are also simplified in this form.
    const std::unordered_set<char> user_function_dependencies; // The User_Functions that the function is defined in
                                                               // terms of e.g. "g(x)" in "f(x) = 5x + 3g(x)".
    const QColor color;
    const int row_number;

    static char find_identifier(std::string expression);
    static char find_variable(std::string expression);

    User_Function(std::unordered_map<char, User_Function> user_function_map, std::string expression,
                             std::unordered_set<char> user_function_dependencies, QColor color, int row_number);
    User_Function(std::string expression, std::string formatted_expression,
                  std::unordered_set<char> user_function_dependencies, QColor color);
    User_Function(const char identifier, const char variable, const std::string expression,
                  std::string formatted_expression, std::unordered_set<char> user_function_dependencies, QColor color);
    std::string call(const std::string argument) const;
};

std::ostream& operator<<(std::ostream& out, User_Function const& user_function);
