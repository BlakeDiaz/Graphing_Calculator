%{
#include <stdlib.h>
#include "Function.hpp"
#include "parser.tab.hpp"
#include "yylex.hpp"
void yyerror(char const *);
%}
%option yylineno noyywrap header-file="lexer.hpp"
%%
[ \t]
[0-9]+"."[0-9]+                 { return yy::parser::make_NUMBER(atof(yytext)); }
[0-9]+                          { return yy::parser::make_NUMBER(atof(yytext)); }
"+"                             { return yy::parser::make_ADD(); }
"-"                             { return yy::parser::make_SUBTRACT(); }
"*"                             { return yy::parser::make_MULTIPLY(); }
"/"                             { return yy::parser::make_DIVIDE(); }
"^"                             { return yy::parser::make_EXPONENT(); }
"("                             { return yy::parser::make_OPEN_PARENTHESIS(); }
")"                             { return yy::parser::make_CLOSE_PARENTHESIS(); }
sqrt                            { return yy::parser::make_FUNCTION(func_map.at("sqrt")); }
asin                            { return yy::parser::make_FUNCTION(func_map.at("asin")); }
acos                            { return yy::parser::make_FUNCTION(func_map.at("acos")); }
atan                            { return yy::parser::make_FUNCTION(func_map.at("atan")); }
sin                             { return yy::parser::make_FUNCTION(func_map.at("sin")); }
cos                             { return yy::parser::make_FUNCTION(func_map.at("cos")); }
tan                             { return yy::parser::make_FUNCTION(func_map.at("tan")); }
abs                             { return yy::parser::make_FUNCTION(func_map.at("abs")); }
log                             { return yy::parser::make_FUNCTION(func_map.at("log")); }
ln                              { return yy::parser::make_FUNCTION(func_map.at("ln")); }
"\n"                            { return yy::parser::make_NEWLINE(); }
<<EOF>>                         { return yy::parser::make_YYEOF(); }
.                               { yyerror("Undefined symbol"); exit(1); }
%%
