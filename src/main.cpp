#include <iostream>
#include <string>
#include <array>
#include <cmath>
#include <map>
#include "Calculator.hpp"

/* Called by yyparse on error. */
void yyerror(char const *s)
{
    std::cout << "oops" << std::endl;
}

int main (int argc, char const* argv[])
{   
    UserFunction my_func = UserFunction('f', 'x', Calculator::format_expression("5sin(x)+3x\n"));

    for (int i = 0; i < 20; ++i)
    {
        std::string value = my_func.call(std::to_string(i));
        std::cout << "Result: " << Calculator::solve_expression(value + "\n") << std::endl;
    }

    return 0;
}
