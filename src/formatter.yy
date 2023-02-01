/* Infix notation calculator */

%skeleton "lalr1.cc" // c++
%require "3.8.2"
%header

%define api.token.raw

%define api.prefix {fmt}
%define api.token.constructor
%define api.value.type variant
%define parse.assert

%{
  #include <iostream>
  #include <cmath>   // For pow, used in the grammar
  void fmterror(char const *);
%}

// The parsing context
%parse-param { std::string& result }

// Enable run-time traces (yydebug)
%define parse.trace

%code
{
  #include "fmtlex.hpp"
}

// Bison declarations
%define api.token.prefix {TOK_}
%token
  ASSIGN "="
  MINUS  "-"
  PLUS   "+"
  STAR   "*"
  SLASH  "/"
  CARAT  "^"
  LPAREN "("
  RPAREN ")"
;
%token NEWLINE "\n"

%precedence "="
%left "-" "+"
%left "*" "/"
%precedence NEG // negation--unary minus
%right "^"      // exponentiation

%token <std::string>  NUM     // Double precision number
%token <std::string> VAR      // Variable (e.g. x, y)
%token <std::string>  FUN     // Function (sin, cos, etc.)
%nterm <std::string> exp 

// Formatting semantic values
%% /* The grammar follows. */
input:
  %empty
| input line
;

line:
  "\n"
| exp "\n"   { std::cout << $1 << std::endl; }
| error "\n" { yyerrok;                      }
;

exp:
  NUM                { $$ += $1;                        }
| FUN "(" exp ")"    { $$ += $1 + "(" + $3 + ")";       }
| exp "+" exp        { $$ += $1 + "+" + $3;             }
| exp "-" exp        { $$ += $1 + "-" + $3;             }
| exp "*" exp        { $$ += $1 + "*" + $3;             }
| exp "/" exp        { $$ += $1 + "/" + $3;             }
| "-" exp  %prec NEG { $$ += "-" + $2;                  }
| exp "^" exp        { $$ += $1 + "^" + $3;             }
| "(" exp ")"        { $$ += "(" + $2 + ")";            }
;
/* End of grammar. */
%%
void fmt::parser::error(const std::string& m)
{
    std::cerr << m << '\n';
}
