#pragma once
#include <string>

typedef double(*func_t)(double);

struct Function
{
  public:
    std::string name;
    func_t ptr;
};
