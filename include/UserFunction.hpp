#pragma once
#include <string>

class UserFunction
{
public:
    const char identifier;          // The 'f' in 'f(x)'
    const char variable;            // The 'x' in 'f(x)'
    const std::string expression;   // Expanded expression with added * symbols and composite functions simplified to make for easier parsing

    UserFunction(const char identifier, const char variable, const std::string expression);
    std::string call(const std::string argument); // Returns expression with the variable being replaced with the argument
};
