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
%parse-param { char& identifier }
%parse-param { char& variable }
%parse-param { bool& function_assignment }

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
  SUBTRACT "-"
  ADD "+"
  MULTIPLY "*"
  DIVIDE "/"
  EXPONENT "^"
  OPEN_PARENTHESIS "("
  CLOSE_PARENTHESIS ")"
;
%token NEWLINE "\n"

%token <std::string> NUMBER // Double precision number
%token <std::string> VARIABLE // Variable (e.g. x, y)
%token <std::string> FUNCTION // Function (sin, cos, etc.)
%token <std::string> USER_FUNCTION_ASSIGNMENT // User-created function assignment (e.g. f(x)=...)
%nterm <std::string> implicit_multiplication_expression
%nterm <std::string> expression 

%precedence VARIABLE
%precedence "="
%left "-" "+"
%left "*" "/"
%precedence NEGATIVE_SIGN // Unary minus operator
%right "^"      // Exponent operator
%nonassoc "(" ")"

// Formatting semantic values
%% /* The grammar follows. */
input:
  %empty
| input line
;

line:
  "\n"
| expression "\n"                           { result = $1;                                                                   }
| USER_FUNCTION_ASSIGNMENT expression "\n"  { result = $2; identifier = $1[0]; variable = $1[2]; function_assignment = true; }
| error "\n"                                { yyerrok;                                                                       }
;

implicit_multiplication_expression:
  VARIABLE                                                          { $$ += "(" + $1 + ")";                                                                                              }
| FUNCTION "(" expression ")"                                       { $$ += $1 + "(" + $3 + ")";                                                                                         }
| VARIABLE "(" expression ")"                                       { $$ += user_function_map.contains($1[0]) ? user_function_map.at($1[0]).call($3) : $1 + "(" + $3 + ")";              }
| "(" expression ")"                                                { $$ += "(" + $2 + ")";                                                                                              }
| implicit_multiplication_expression VARIABLE                       { $$ += $1 + "*" + "(" + $2 + ")";                                                                                   }
| implicit_multiplication_expression FUNCTION "(" expression ")"    { $$ += $1 + "*" + $2 + "(" + $4 + ")";                                                                              }
| implicit_multiplication_expression VARIABLE "(" expression ")"    { $$ += $1 + "*" + (user_function_map.contains($2[0]) ? user_function_map.at($2[0]).call($4) : $2 + "(" + $4 + ")"); }
| implicit_multiplication_expression "(" expression ")"             { $$ += $1 + "*" + "(" + $3 + ")";                                                                                   }

expression:
  NUMBER                                    { $$ += $1;                   }
| implicit_multiplication_expression        { $$ += $1;                   }
| NUMBER implicit_multiplication_expression { $$ += $1 + "*(" + $2 + ")"; }
| expression "+" expression                 { $$ += $1 + "+" + $3;        }
| expression "-" expression                 { $$ += $1 + "-" + $3;        }
| expression "*" expression                 { $$ += $1 + "*" + $3;        }
| expression "/" expression                 { $$ += $1 + "/" + $3;        }
| "-" expression  %prec NEGATIVE_SIGN       { $$ += "-" + $2;             }
| expression "^" expression                 { $$ += $1 + "^" + $3;        }
;
/* End of grammar. */
%%
void fmt::parser::error(const std::string& m)
{
    std::cerr << m << '\n';
}
