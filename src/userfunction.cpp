#include "UserFunction.hpp"
#include <sstream>

/**
 * Class constructor.
 *
 * @param identifier The letter that identifies the function e.g. the "f" in "f(x) = 5x + 3".
 * @param variable The variable that the function uses e.g. the "x" in "f(x) = 5x + 3".
 * @param expression The text form of the function e.g. "f(x) = 5x + 3".
 * @param formatted_expression The body of the function formatted to make it easier to parse e.g. "5*x+3" from the expression "f(x) = 5x + 3".
 * @param user_function_dependencies The UserFunctions that the function is defined in terms of e.g. "g(x)" in "f(x) = 5x + 3g(x)".
 */
UserFunction::UserFunction(const char identifier, const char variable, const std::string expression, std::string formatted_expression, std::set<char> user_function_dependencies)
    : identifier(identifier), variable(variable), expression(expression), formatted_expression(formatted_expression), user_function_dependencies(user_function_dependencies)
{
}

/**
 * Replaces each instance of the function's variable with the provided argument.
 * For example, if the UserFunction is "f(x)=5*x+3" and the argument passed in is "15", the result
 * will be "5*(15)+3".
 *
 * @param argument The string that replaces each instance of` the function's variable. 
 */
std::string UserFunction::call(const std::string argument)
{
    // Wrap argument in parenthesis
    std::stringstream argument_stream;
    argument_stream << '(' << argument << ')';
    std::string modified_argument = argument_stream.str();
    
    // Wrap variable in parenthesis (We do this originally in the formatter so we don't replace non-variable text)
    std::stringstream variable_stream;
    variable_stream << '(' << variable << ')';
    std::string modified_variable = variable_stream.str();

    // Make a copy of expression to modify
    std::string new_expression = expression;

    // Replaces each instance of the function's variable with the provided argument
    size_t start_position = 0;
    while ((start_position = new_expression.find(modified_variable, start_position)) != std::string::npos)
    {
        new_expression.replace(start_position, modified_variable.length(), modified_argument);
        start_position += modified_argument.length();
    }
    
    return new_expression;
}
