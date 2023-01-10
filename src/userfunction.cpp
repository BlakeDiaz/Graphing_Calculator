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
    argument_stream << '(';
    argument_stream << argument;
    argument_stream << ')';
    std::string modified_argument = argument_stream.str();
    
    // Replaces each instance of the function's variable with the provided argument
    std::string new_expression;
    for (int i = 0; i < expression.length(); ++i)
    {
        const char current_char = expression[i];
        if (current_char != variable)
        {
            new_expression.push_back(current_char);
            continue;
        }
        // Checks if character before current one is a letter (if so current_char is part of a function like sin())
        if (i > 0 && is_letter(expression[i-1]))
        {
            new_expression.push_back(current_char);
            continue;
        }
        // Checks if character after current one is a letter (if so current_char is part of a function like sin())
        if (i < expression.length() - 1 && is_letter(expression[i+1]))
        {
            new_expression.push_back(current_char);
            continue;
        }
        // At this point, we are certain that the character in question is the variable we want to replace
        new_expression.append(modified_argument);
    }
    
    // Optionally simplify expression here with a computer algebra system like maxima

    return new_expression;
}
