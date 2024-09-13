%{
#include "formatter.tab.hpp"
#include "fmtlex.hpp"
#define YY_USER_ACTION parse_error.location.columns(yyleng);
%}
%option noyywrap prefix="fmt" header-file="formatter_lexer.hpp"

letter [a-zA-Z]
whitespace [ \t]*
%%
%{
    parse_error.location.step();
%}
[ \t]                           { parse_error.location.step(); }
[0-9]+"."[0-9]+                 { return fmt::parser::make_NUMBER(yytext, parse_error.location); }
[0-9]+                          { return fmt::parser::make_NUMBER(yytext, parse_error.location); }
{letter}{whitespace}\({whitespace}{letter}{whitespace}\){whitespace}=  { return fmt::parser::make_USER_FUNCTION_ASSIGNMENT(yytext, parse_error.location);  }
"+"                             { return fmt::parser::make_ADD(parse_error.location); }
"-"                             { return fmt::parser::make_SUBTRACT(parse_error.location); }
"*"                             { return fmt::parser::make_MULTIPLY(parse_error.location); }
"/"                             { return fmt::parser::make_DIVIDE(parse_error.location); }
"^"                             { return fmt::parser::make_EXPONENT(parse_error.location); }
"("                             { return fmt::parser::make_OPEN_PARENTHESIS(parse_error.location); }
")"                             { return fmt::parser::make_CLOSE_PARENTHESIS(parse_error.location); }
sqrt                            { return fmt::parser::make_FUNCTION("sqrt", parse_error.location); }
asin                            { return fmt::parser::make_FUNCTION("asin", parse_error.location); }
acos                            { return fmt::parser::make_FUNCTION("acos", parse_error.location); }
atan                            { return fmt::parser::make_FUNCTION("atan", parse_error.location); }
sin                             { return fmt::parser::make_FUNCTION("sin", parse_error.location); }
cos                             { return fmt::parser::make_FUNCTION("cos", parse_error.location); }
tan                             { return fmt::parser::make_FUNCTION("tan", parse_error.location); }
abs                             { return fmt::parser::make_FUNCTION("abs", parse_error.location); }
log                             { return fmt::parser::make_FUNCTION("log", parse_error.location); }
ln                              { return fmt::parser::make_FUNCTION("ln", parse_error.location); }
[a-zA-Z]                        { return fmt::parser::make_VARIABLE(yytext, parse_error.location); }
"\n"                            { return fmt::parser::make_NEWLINE(parse_error.location); }
<<EOF>>                         { return fmt::parser::make_YYEOF(parse_error.location); }
.                               { throw fmt::parser::syntax_error(parse_error.location, "Undefined symbol in formatter"); }
%%
