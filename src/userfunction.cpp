#include "UserFunction.hpp"
#include "Calculator.hpp"
#include "string_manipulation.hpp"
#include <sstream>

/**
 * Finds the identifier of a UserFunction's expression.
 * This should only be called if the expression has been verified to be a UserFunction definition.
 * To verify that, use Calculator::identify_function().
 *
 * @param expression The text form of the function e.g. "f(x) = 5x + 3
 * @return The letter that identifies the function e.g. the "f" in "f(x) = 5x + 3".
 */
char UserFunction::find_identifier(std::string expression)
{
    std::string modified_expression = remove_whitespace(expression);

    return modified_expression[0];
}

/**
 * Finds the variable of a UserFunction's expression.
 * This should only be called if the expression has been verified to be a UserFunction definition.
 * To verify that, use Calculator::identify_function().
 *
 * @param expression The text form of the function e.g. "f(x) = 5x + 3
 * @return The variable that the function uses e.g. the "x" in "f(x) = 5x + 3".
 */
char UserFunction::find_variable(std::string expression)
{
    std::string modified_expression = remove_whitespace(expression);

    return modified_expression[2];
}

/**
 * Class constructor.
 *
 * @param user_function_map An unordered map containing each user-defined function.
 * @param expression The text form of the function e.g. "f(x) = 5x + 3".
 * @param formatted_expression The body of the function formatted to make it easier to parse e.g. "5*x+3" from the expression "f(x) = 5x + 3".
 */
UserFunction::UserFunction(std::unordered_map<char, UserFunction> user_function_map, std::string expression)
    : identifier(find_identifier(expression)),
    variable(find_variable(expression)),
    expression(expression),
    formatted_expression(Calculator::format_expression(user_function_map, expression)),
    user_function_dependencies(Calculator::locate_user_function_dependencies(user_function_map, expression))
{
}

/**
 * Class constructor.
 *
 * @param expression The text form of the function e.g. "f(x) = 5x + 3".
 */
UserFunction::UserFunction(std::string expression, std::string formatted_expression, std::unordered_set<char> user_function_dependencies)
    : identifier(find_identifier(expression)), variable(find_variable(expression)), expression(expression), formatted_expression(formatted_expression), user_function_dependencies(user_function_dependencies)
{
}

/**
 * Class constructor.
 *
 * @param identifier The letter that identifies the function e.g. the "f" in "f(x) = 5x + 3".
 * @param variable The variable that the function uses e.g. the "x" in "f(x) = 5x + 3".
 * @param expression The text form of the function e.g. "f(x) = 5x + 3".
 * @param formatted_expression The body of the function formatted to make it easier to parse e.g. "5*x+3" from the expression "f(x) = 5x + 3".
 * @param user_function_dependencies The UserFunctions that the function is defined in terms of e.g. "g(x)" in "f(x) = 5x + 3g(x)".
 */
UserFunction::UserFunction(const char identifier, const char variable, const std::string expression, std::string formatted_expression, std::unordered_set<char> user_function_dependencies)
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

    // Make a copy of the formatted expression to modify
    std::string new_expression = formatted_expression;

    // Replaces each instance of the function's variable with the provided argument
    size_t start_position = 0;
    while ((start_position = new_expression.find(modified_variable, start_position)) != std::string::npos)
    {
        new_expression.replace(start_position, modified_variable.length(), modified_argument);
        start_position += modified_argument.length();
    }
    
    return new_expression;
}
