#pragma once
#include <functional>
#include <string>

typedef std::function<double(double)> func_t;

struct Function
{
public:
    std::string name;
    func_t ptr;
};
