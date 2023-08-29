%{
#include "formatter.tab.hpp"
#include "fmtlex.hpp"
void yyerror(char const *);
%}
%option yylineno noyywrap prefix="fmt" header-file="formatter_lexer.hpp"
%%
[ \t]
[0-9]+"."[0-9]+                 { return fmt::parser::make_NUMBER(yytext); }
[0-9]+                          { return fmt::parser::make_NUMBER(yytext); }
[a-z]\([a-z]\)=                 { return fmt::parser::make_USER_FUNCTION_ASSIGNMENT(yytext); }
"+"                             { return fmt::parser::make_ADD(); }
"-"                             { return fmt::parser::make_SUBTRACT(); }
"*"                             { return fmt::parser::make_MULTIPLY(); }
"/"                             { return fmt::parser::make_DIVIDE(); }
"^"                             { return fmt::parser::make_EXPONENT(); }
"("                             { return fmt::parser::make_OPEN_PARENTHESIS(); }
")"                             { return fmt::parser::make_CLOSE_PARENTHESIS(); }
sqrt                            { return fmt::parser::make_FUNCTION("sqrt"); }
asin                            { return fmt::parser::make_FUNCTION("asin"); }
acos                            { return fmt::parser::make_FUNCTION("acos"); }
atan                            { return fmt::parser::make_FUNCTION("atan"); }
sin                             { return fmt::parser::make_FUNCTION("sin"); }
cos                             { return fmt::parser::make_FUNCTION("cos"); }
tan                             { return fmt::parser::make_FUNCTION("tan"); }
abs                             { return fmt::parser::make_FUNCTION("abs"); }
log                             { return fmt::parser::make_FUNCTION("log"); }
ln                              { return fmt::parser::make_FUNCTION("ln"); }
[a-zA-Z]                        { return fmt::parser::make_VARIABLE(yytext); }
"\n"                            { return fmt::parser::make_NEWLINE(); }
<<EOF>>                         { return fmt::parser::make_YYEOF(); }
.                               { yyerror("Undefined symbol"); exit(1); }
%%
