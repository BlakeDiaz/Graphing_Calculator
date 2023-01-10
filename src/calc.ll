%{
#include <stdlib.h>
#include "Function.hpp"
#include "calc.tab.hpp"
#include "yylex.hpp"
void yyerror(char const *);
%}
%option noyywrap
%%
[ \t]
[0-9]+"."[0-9]+                 { return yy::parser::make_NUM(atof(yytext)); }
[0-9]+                          { return yy::parser::make_NUM(atof(yytext)); }
"+"                             { return yy::parser::make_PLUS(); }
"-"                             { return yy::parser::make_MINUS(); }
"*"                             { return yy::parser::make_STAR(); }
"/"                             { return yy::parser::make_SLASH(); }
"^"                             { return yy::parser::make_CARAT(); }
"("                             { return yy::parser::make_LPAREN(); }
")"                             { return yy::parser::make_RPAREN(); }
sqrt                            { return yy::parser::make_FUN(func_map.at("sqrt")); }
asin                            { return yy::parser::make_FUN(func_map.at("asin")); }
acos                            { return yy::parser::make_FUN(func_map.at("acos")); }
atan                            { return yy::parser::make_FUN(func_map.at("atan")); }
sin                             { return yy::parser::make_FUN(func_map.at("sin")); }
cos                             { return yy::parser::make_FUN(func_map.at("cos")); }
tan                             { return yy::parser::make_FUN(func_map.at("tan")); }
abs                             { return yy::parser::make_FUN(func_map.at("abs")); }
log                             { return yy::parser::make_FUN(func_map.at("log")); }
ln                              { return yy::parser::make_FUN(func_map.at("ln")); }
"\n"                            { return yy::parser::make_NEWLINE(); }
<<EOF>>                         { return yy::parser::make_YYEOF(); }
.                               { yyerror("Undefined symbol"); exit(1); }
%%
