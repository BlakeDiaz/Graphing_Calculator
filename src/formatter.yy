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
  void yyerror(char const *);
%}

%code requires
{
  #include "Function.hpp" // Includes func_map variable, and Function type
  #include <map>
}

// The parsing context
%param { std::map<std::string, Function>& func_map }

// Enable run-time traces (yydebug)
%define parse.trace

%code
{
  #include "yylex.hpp"
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

%token <double>  NUM     // Double precision number
%token <Function> FUN // Function (sin, cos, etc.)
%nterm <double>  exp

// Formatting semantic values
%printer { std::cout << $$.name << "()"; } FUN;
%printer { std::cout << $$; } <double>;

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
  NUM                { $$ = $1;                         }
| FUN "(" exp ")"    { $$ = $1.ptr($3);                 }
| exp "+" exp        { $$ = $1 + $3;                    }
| exp "-" exp        { $$ = $1 - $3;                    }
| exp "*" exp        { $$ = $1 * $3;                    }
| exp "/" exp        { $$ = $1 / $3;                    }
| "-" exp  %prec NEG { $$ = -$2;                        }
| exp "^" exp        { $$ = pow($1, $3);                }
| "(" exp ")"        { $$ = $2;                         }
;
/* End of grammar. */
%%
void yy::parser::error(const std::string& m)
{
    std::cerr << m << '\n';
}
