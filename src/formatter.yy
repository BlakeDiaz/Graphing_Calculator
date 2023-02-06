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
  #include "fmtlex.hpp"
  void fmterror(char const *);
%}

// The parsing context
%parse-param { std::unordered_map<char, UserFunction>& user_function_map }
%parse-param { std::string& result }

// Enable run-time traces (yydebug)
%define parse.trace

%code requires
{
  #include <unordered_map>
  #include "UserFunction.hpp"
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
%token <std::string> ID      // Variable (e.g. x, y)
%token <std::string>  FUN     // Function (sin, cos, etc.)
%nterm <std::string> implicit
%nterm <std::string> exp 

// Formatting semantic values
%% /* The grammar follows. */
input:
  %empty
| input line
;

line:
  "\n"
| exp "\n"   { result = $1; }
| error "\n" { yyerrok;                      }
;

implicit:
  ID                           { $$ += "(" + $1 + ")";                 }
| FUN "(" exp ")"               { $$ += $1 + "(" + $3 + ")";            }
| ID "(" exp ")"                { $$ += user_function_map.contains($1[0]) ? user_function_map.at($1[0]).call($3) : $1 + "(" + $3 + ")"; }
| "(" exp ")"                   { $$ += "(" + $2 + ")";                 }
| implicit ID                  { $$ += $1 + "*" + "(" + $2 + ")";      }
| implicit FUN "(" exp ")"      { $$ += $1 + "*" + $2 + "(" + $4 + ")"; }
| implicit ID "(" exp ")"       { $$ += $1 + "*" + (user_function_map.contains($2[0]) ? user_function_map.at($2[0]).call($4) : $2 + "(" + $4 + ")"); }
| implicit "(" exp ")"          { $$ += $1 + "*" + "(" + $3 + ")";      }

exp:
  NUM                { $$ += $1;                        }
| implicit           { $$ += $1;                        }
| NUM implicit       { $$ += $1 + "*(" + $2 + ")";      }
| exp "+" exp        { $$ += $1 + "+" + $3;             }
| exp "-" exp        { $$ += $1 + "-" + $3;             }
| exp "*" exp        { $$ += $1 + "*" + $3;             }
| exp "/" exp        { $$ += $1 + "/" + $3;             }
| "-" exp  %prec NEG { $$ += "-" + $2;                  }
| exp "^" exp        { $$ += $1 + "^" + $3;             }
;
/* End of grammar. */
%%
void fmt::parser::error(const std::string& m)
{
    std::cerr << m << '\n';
}
