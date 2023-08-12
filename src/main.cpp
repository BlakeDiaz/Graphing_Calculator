#include <iostream>
#include <optional>
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

int main(int argc, char const* argv[])
{
    std::unordered_map<char, UserFunction> user_function_map;
    auto&&[formatted_expression, possible_user_function] = Calculator::format_expression(user_function_map, "f(x)=x^2\n");

    std::cout << "Is a function: " << (possible_user_function.has_value() ? "True" : "False") << std::endl;
    
    if (possible_user_function.has_value())
    {
        std::cout << "Identifier: " << possible_user_function->identifier << std::endl;
        std::cout << "Variable: " << possible_user_function->variable << std::endl;
        std::cout << "Expression: " << possible_user_function->expression << std::endl;
        std::cout << "Number of Dependencies: " << possible_user_function->user_function_dependencies.size() << std::endl;
    }

    std::cout << "Formatted Expression: " << formatted_expression << std::endl;
        
    return 0;
}
