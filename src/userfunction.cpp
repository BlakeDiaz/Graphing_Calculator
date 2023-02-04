#include "UserFunction.hpp"
#include <sstream>

bool is_letter(const char c)
{
    if (c >= 'a' && c <= 'z')
    {
        return true;
    }

    return false;
}

UserFunction::UserFunction(const char identifier, const char variable, const std::string expression)
    : identifier(identifier), variable(variable), expression(expression)
{
}

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
