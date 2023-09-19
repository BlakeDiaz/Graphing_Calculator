%{
#include "user_function_dependency_locator.tab.hpp"
#include "ufdllex.hpp"
void yyerror(char const *);
%}
%option yylineno noyywrap prefix="ufdl" header-file="user_function_dependency_locator_lexer.hpp"
%%
[ \t]
[0-9]+"."[0-9]+                 { return ufdl::parser::make_NUMBER(); }
[0-9]+                          { return ufdl::parser::make_NUMBER(); }
[a-z]\([a-z]\)=                 { return ufdl::parser::make_USER_FUNCTION_ASSIGNMENT(); }
"+"                             { return ufdl::parser::make_ADD(); }
"-"                             { return ufdl::parser::make_SUBTRACT(); }
"*"                             { return ufdl::parser::make_MULTIPLY(); }
"/"                             { return ufdl::parser::make_DIVIDE(); }
"^"                             { return ufdl::parser::make_EXPONENT(); }
"("                             { return ufdl::parser::make_OPEN_PARENTHESIS(); }
")"                             { return ufdl::parser::make_CLOSE_PARENTHESIS(); }
sqrt                            { return ufdl::parser::make_FUNCTION(); }
asin                            { return ufdl::parser::make_FUNCTION();}
acos                            { return ufdl::parser::make_FUNCTION(); }
atan                            { return ufdl::parser::make_FUNCTION(); }
sin                             { return ufdl::parser::make_FUNCTION(); }
cos                             { return ufdl::parser::make_FUNCTION(); }
tan                             { return ufdl::parser::make_FUNCTION(); }
abs                             { return ufdl::parser::make_FUNCTION(); }
log                             { return ufdl::parser::make_FUNCTION(); }
ln                              { return ufdl::parser::make_FUNCTION(); }
[a-zA-Z]                        { return ufdl::parser::make_VARIABLE(yytext); }
"\n"                            { return ufdl::parser::make_NEWLINE(); }
<<EOF>>                         { return ufdl::parser::make_YYEOF(); }
.                               { yyerror("Undefined symbol in user function dependency locator"); exit(1); }
%%
