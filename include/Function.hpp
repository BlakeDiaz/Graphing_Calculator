#pragma once
#include <functional>
#include <string>

typedef double(*func_t)(double);

struct Function
{
  public:
    std::string name;
    func_t ptr;
};
