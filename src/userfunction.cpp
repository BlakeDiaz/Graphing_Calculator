#include "User_Function.hpp"
#include "Calculator.hpp"
#include "string_manipulation.hpp"
#include <sstream>

/**
 * Prints a User_Function using std::cout.
 *
 * @param out std::cout.
 * @param user_function The user_function to be printed.
 */
std::ostream& operator<<(std::ostream& out, User_Function const& user_function)
{
    out << "Identifier: " << user_function.identifier << "; ";
    out << "Variable: " << user_function.variable << "; ";
    out << "Expression: " << user_function.expression << "; ";
    out << "Formatted Expression: " << user_function.formatted_expression << "; ";
    out << "Number of Dependencies: " << user_function.user_function_dependencies.size() << "; ";

    return out;
}

/**
 * Finds the identifier of a User_Function's expression.
 * This should only be called if the expression has been verified to be a User_Function definition.
 * To verify that, use Calculator::identify_function().
 *
 * @param expression The text form of the function e.g. "f(x) = 5x + 3
 * @return The letter that identifies the function e.g. the "f" in "f(x) = 5x + 3".
 */
char User_Function::find_identifier(std::string expression)
{
    std::string modified_expression = remove_whitespace(expression);

    return modified_expression[0];
}

/**
 * Finds the variable of a User_Function's expression.
 * This should only be called if the expression has been verified to be a User_Function definition.
 * To verify that, use Calculator::identify_function().
 *
 * @param expression The text form of the function e.g. "f(x) = 5x + 3
 * @return The variable that the function uses e.g. the "x" in "f(x) = 5x + 3".
 */
char User_Function::find_variable(std::string expression)
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
User_Function::User_Function(std::unordered_map<char, User_Function> user_function_map, std::string expression)
    : identifier(find_identifier(expression)),
    variable(find_variable(expression)),
    expression(expression),
    formatted_expression(Calculator::format_expression(user_function_map, expression)),
    user_function_dependencies(Calculator::locate_user_function_dependencies(expression))
{
}

/**
 * Class constructor.
 *
 * @param expression The text form of the function e.g. "f(x) = 5x + 3".
 */
User_Function::User_Function(std::string expression, std::string formatted_expression, std::unordered_set<char> user_function_dependencies)
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
 * @param user_function_dependencies The User_Functions that the function is defined in terms of e.g. "g(x)" in "f(x) = 5x + 3g(x)".
 */
User_Function::User_Function(const char identifier, const char variable, const std::string expression, std::string formatted_expression, std::unordered_set<char> user_function_dependencies)
    : identifier(identifier), variable(variable), expression(expression), formatted_expression(formatted_expression), user_function_dependencies(user_function_dependencies)
{
}

/**
 * Replaces each instance of the function's variable with the provided argument.
 * For example, if the User_Function is "f(x)=5*x+3" and the argument passed in is "15", the result
 * will be "5*(15)+3".
 *
 * @param argument The string that replaces each instance of` the function's variable. 
 */
std::string User_Function::call(const std::string argument) const
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
