%{
#include <stdlib.h>
#include "Function.hpp"
#include "parser.tab.hpp"
#include "yylex.hpp"
#define YY_USER_ACTION parse_error.location.columns(yyleng);
%}
%option noyywrap header-file="lexer.hpp"
%%
%{
    parse_error.location.step();
%}
[ \t]                           { parse_error.location.step(); }
[0-9]+"."[0-9]+                 { return yy::parser::make_NUMBER(atof(yytext), parse_error.location); }
[0-9]+                          { return yy::parser::make_NUMBER(atof(yytext), parse_error.location); }
"+"                             { return yy::parser::make_ADD(parse_error.location); }
"-"                             { return yy::parser::make_SUBTRACT(parse_error.location); }
"*"                             { return yy::parser::make_MULTIPLY(parse_error.location); }
"/"                             { return yy::parser::make_DIVIDE(parse_error.location); }
"^"                             { return yy::parser::make_EXPONENT(parse_error.location); }
"("                             { return yy::parser::make_OPEN_PARENTHESIS(parse_error.location); }
")"                             { return yy::parser::make_CLOSE_PARENTHESIS(parse_error.location); }
sqrt                            { return yy::parser::make_FUNCTION(func_map.at("sqrt"), parse_error.location); }
asin                            { return yy::parser::make_FUNCTION(func_map.at("asin"), parse_error.location); }
acos                            { return yy::parser::make_FUNCTION(func_map.at("acos"), parse_error.location); }
atan                            { return yy::parser::make_FUNCTION(func_map.at("atan"), parse_error.location); }
sin                             { return yy::parser::make_FUNCTION(func_map.at("sin"), parse_error.location); }
cos                             { return yy::parser::make_FUNCTION(func_map.at("cos"), parse_error.location); }
tan                             { return yy::parser::make_FUNCTION(func_map.at("tan"), parse_error.location); }
abs                             { return yy::parser::make_FUNCTION(func_map.at("abs"), parse_error.location); }
log                             { return yy::parser::make_FUNCTION(func_map.at("log"), parse_error.location); }
ln                              { return yy::parser::make_FUNCTION(func_map.at("ln"), parse_error.location); }
"\n"                            { return yy::parser::make_NEWLINE(parse_error.location); }
<<EOF>>                         { return yy::parser::make_YYEOF(parse_error.location); }
.                               { throw yy::parser::syntax_error(parse_error.location, "Undefined symbol in solver"); }
%%
