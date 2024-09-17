%{
#include "user_function_dependency_locator.tab.hpp"
#include "ufdllex.hpp"
#define YY_USER_ACTION parse_error.location.columns(yyleng);
%}
%option noyywrap prefix="ufdl" header-file="user_function_dependency_locator_lexer.hpp"

letter [a-zA-Z]
whitespace [ \t]*
%%
%{
    parse_error.location.step();
%}
[ \t]                           { parse_error.location.step(); }
[0-9]+"."[0-9]+                 { return ufdl::parser::make_NUMBER(parse_error.location); }
[0-9]+                          { return ufdl::parser::make_NUMBER(parse_error.location); }
{letter}{whitespace}\({whitespace}{letter}{whitespace}\){whitespace}=  { return ufdl::parser::make_USER_FUNCTION_ASSIGNMENT(parse_error.location);  }
"+"                             { return ufdl::parser::make_ADD(parse_error.location); }
"-"                             { return ufdl::parser::make_SUBTRACT(parse_error.location); }
"*"                             { return ufdl::parser::make_MULTIPLY(parse_error.location); }
"/"                             { return ufdl::parser::make_DIVIDE(parse_error.location); }
"^"                             { return ufdl::parser::make_EXPONENT(parse_error.location); }
"("                             { return ufdl::parser::make_OPEN_PARENTHESIS(parse_error.location); }
")"                             { return ufdl::parser::make_CLOSE_PARENTHESIS(parse_error.location); }
sqrt                            { return ufdl::parser::make_FUNCTION(parse_error.location); }
asin                            { return ufdl::parser::make_FUNCTION(parse_error.location);}
acos                            { return ufdl::parser::make_FUNCTION(parse_error.location); }
atan                            { return ufdl::parser::make_FUNCTION(parse_error.location); }
sin                             { return ufdl::parser::make_FUNCTION(parse_error.location); }
cos                             { return ufdl::parser::make_FUNCTION(parse_error.location); }
tan                             { return ufdl::parser::make_FUNCTION(parse_error.location); }
abs                             { return ufdl::parser::make_FUNCTION(parse_error.location); }
log                             { return ufdl::parser::make_FUNCTION(parse_error.location); }
ln                              { return ufdl::parser::make_FUNCTION(parse_error.location); }
[a-zA-Z]                        { return ufdl::parser::make_VARIABLE(yytext, parse_error.location); }
"\n"                            { return ufdl::parser::make_NEWLINE(parse_error.location); }
<<EOF>>                         { return ufdl::parser::make_YYEOF(parse_error.location); }
.                               { throw ufdl::parser::syntax_error(parse_error.location, "Undefined symbol in user function dependency locator"); }
%%
