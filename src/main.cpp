#include <iostream>
#include <string>
#include <array>
#include <cmath>
#include <unordered_map>
#include "Calculator.hpp"

/* Called by yyparse on error. */
void yyerror(char const *s)
{
    std::cout << s << std::endl;
}

int main (int argc, char const* argv[])
{
    std::unordered_map<char, UserFunction> user_function_map;
    auto&&[formatted_expression, identifier, variable, function_assignment] = Calculator::format_expression(user_function_map, "f(x)=x^2\n");

    std::cout << "Expression: " << formatted_expression << std::endl;
    std::cout << "Identifier: " << identifier << std::endl;
    std::cout << "Variable: " << variable << std::endl;
    std::cout << "Is a function assignment: " << (function_assignment ? "True" : "False") << std::endl;

    return 0;
}
