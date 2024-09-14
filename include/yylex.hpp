#pragma once
#include <map>
#include <string>

// Flex expects yylex to be defined in the macro YY_DECL
#define YY_DECL yy::parser::symbol_type yylex(Parse_Error& parse_error, const std::unordered_map<std::string, Function>& func_map)
