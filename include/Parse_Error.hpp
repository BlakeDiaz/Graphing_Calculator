#pragma once
#include <location.hpp>
#include <string>

struct Parse_Error
{
    ufdl::location location;
    std::string expression;

    Parse_Error(int line_number, std::string expression);
};
