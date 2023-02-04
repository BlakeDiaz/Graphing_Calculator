#include <iostream>
#include <string>
#include <array>
#include <cmath>
#include <map>
#include "Function.hpp"
#include "parser.tab.hpp"
#include "formatter.tab.hpp"
#include "lexer.hpp"
#include "formatter_lexer.hpp"

const std::unordered_map<std::string, Function> init_func_map()
{
    std::unordered_map<std::string, Function> func_map;
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

std::string format_expression(std::string expression)
{
    std::string result;

    YY_BUFFER_STATE bs = fmt_scan_string(expression.c_str());
    yy_switch_to_buffer(bs);

    fmt::parser formatter(result);
    formatter();

    yy_delete_buffer(bs);

    return result;
}

double solve_expression(const std::unordered_map<std::string, Function> func_map, std::string expression)
{
    double result;
    
    YY_BUFFER_STATE bs = yy_scan_string(expression.c_str());
    yy_switch_to_buffer(bs);

    yy::parser parser(func_map, result);
    parser();

    yy_delete_buffer(bs);

    return result;
}

int main (int argc, char const* argv[])
{
    double result;
    const std::unordered_map<std::string, Function> func_map = init_func_map();
    
    std::cout << "Answer 1: " << solve_expression(func_map, "20 * 9\n") << std::endl;
    std::cout << "Formatting:" << format_expression("5sin(3x)cos(5-4)-32x^4\n") << std::endl;

    return 0;
}
