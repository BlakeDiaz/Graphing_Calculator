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
    std::cout << "Answer 1: " << Calculator::solve_expression("20 * 9\n") << std::endl;
    std::cout << "Formatting:" << Calculator::format_expression("5sin(3x)cos(5-4)-32x^4\n") << std::endl;

    return 0;
}
