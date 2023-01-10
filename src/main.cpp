#include <iostream>
#include <string>
#include <array>
#include <cmath>
#include <map>
#include "Function.hpp"
#include "parser.tab.hpp"

 std::map<std::string, Function> init_func_map()
{
    std::map<std::string, Function> func_map;
    std::array<std::string, 9> func_names = { "sin", "cos", "tan", "asin", "acos", "atan", "log", "ln", "sqrt" };
    std::array<func_t, 9> functions = { sin, cos, tan, asin, acos, atan, log10, log, sqrt };
    for (int i = 0; i < func_names.size(); ++i)
    {
        Function function = { .name = func_names[i], .ptr = functions[i] };
        func_map[function.name] = function;
    }
    return func_map;
}

/* Called by yyparse on error. */
void yyerror(char const *s)
{
    std::cout << "oops" << std::endl;
}

int main (int argc, char const* argv[])
{
    std::map<std::string, Function> func_map = init_func_map();
    yy::parser parsed(func_map);
    return parsed();
}
