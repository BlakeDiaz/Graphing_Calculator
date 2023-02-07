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
    UserFunction my_func = UserFunction('f', 'x', Calculator::format_expression(user_function_map, "5sin(x)+3x\n"));
    user_function_map.emplace(my_func.identifier, my_func);

    std::cout << Calculator::format_expression(user_function_map, "5f(x)\n") << std::endl; 

    /*for (int i = 0; i < 20; ++i)
    {
        std::string value = my_func.call(std::to_string(i));
        std::cout << "Result: " << Calculator::solve_expression(value + "\n") << std::endl;
    }*/

    return 0;
}
