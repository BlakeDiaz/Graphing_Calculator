#pragma once
#include <string>
#include <map>

// Flex expects yylex to be defined in the macro YY_DECL
#define YY_DECL yy::parser::symbol_type yylex(const std::unordered_map<std::string, Function>& func_map)
