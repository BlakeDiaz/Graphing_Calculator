%{
#include "formatter.tab.hpp"
#include "fmtlex.hpp"
void yyerror(char const *);
%}
%option noyywrap prefix="fmt" header-file="formatter_lexer.hpp"
%%
[ \t]
[0-9]+"."[0-9]+                 { return fmt::parser::make_NUM(yytext); }
[0-9]+                          { return fmt::parser::make_NUM(yytext); }
[a-z]\([a-z]\)=                 { return fmt::parser::make_ASSIGN(yytext); }
"+"                             { return fmt::parser::make_PLUS(); }
"-"                             { return fmt::parser::make_MINUS(); }
"*"                             { return fmt::parser::make_STAR(); }
"/"                             { return fmt::parser::make_SLASH(); }
"^"                             { return fmt::parser::make_CARAT(); }
"("                             { return fmt::parser::make_LPAREN(); }
")"                             { return fmt::parser::make_RPAREN(); }
sqrt                            { return fmt::parser::make_FUN("sqrt"); }
asin                            { return fmt::parser::make_FUN("asin"); }
acos                            { return fmt::parser::make_FUN("acos"); }
atan                            { return fmt::parser::make_FUN("atan"); }
sin                             { return fmt::parser::make_FUN("sin"); }
cos                             { return fmt::parser::make_FUN("cos"); }
tan                             { return fmt::parser::make_FUN("tan"); }
abs                             { return fmt::parser::make_FUN("abs"); }
log                             { return fmt::parser::make_FUN("log"); }
ln                              { return fmt::parser::make_FUN("ln"); }
[a-zA-Z]                        { return fmt::parser::make_ID(yytext); }
"\n"                            { return fmt::parser::make_NEWLINE(); }
<<EOF>>                         { return fmt::parser::make_YYEOF(); }
.                               { yyerror("Undefined symbol"); exit(1); }
%%
