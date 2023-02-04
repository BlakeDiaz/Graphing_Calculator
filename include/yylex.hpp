#pragma once
#include <string>
#include <map>
#include "Function.hpp"
#include "parser.tab.hpp"
// Give flex the prototype of yylex we want...
#define YY_DECL \
    yy::parser::symbol_type yylex(const std::unordered_map<std::string, Function>& func_map)
// ... and declare it for the parser's sake.
YY_DECL;
