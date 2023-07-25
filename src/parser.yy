/* Infix notation calculator */

%skeleton "lalr1.cc" // c++
%require "3.8.2"
%header

%define api.token.raw

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
%param { const std::unordered_map<std::string, Function>& func_map }
%parse-param { double& result }

// Enable run-time traces (yydebug)
%define parse.trace

%code
{
  #include "yylex.hpp"
  YY_DECL;
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

%precedence "="
%left "-" "+"
%left "*" "/"
%precedence NEGATIVE_SIGN // Unary minus operator
%right "^"      // Exponent operator

%token <double>  NUMBER     // Double precision number
%token <Function> FUNCTION // Function (sin, cos, etc.)
%nterm <double>  expression

// Formatting semantic values
%printer { std::cout << $$.name << "()"; } FUNCTION;
%printer { std::cout << $$; } <double>;

%% /* The grammar follows. */
input:
  %empty
| input line
;

line:
  "\n"
| expression "\n"   { result = $1; }
| error "\n"        { yyerrok;     }
;

expression:
  NUMBER                                { $$ = $1;          }
| FUNCTION "(" expression ")"           { $$ = $1.ptr($3);  }
| expression "+" expression             { $$ = $1 + $3;     }
| expression "-" expression             { $$ = $1 - $3;     }
| expression "*" expression             { $$ = $1 * $3;     }
| expression "/" expression             { $$ = $1 / $3;     }
| "-" expression  %prec NEGATIVE_SIGN   { $$ = -$2;         }
| expression "^" expression             { $$ = pow($1, $3); }
| "(" expression ")"                    { $$ = $2;          }
;
/* End of grammar. */
%%
void yy::parser::error(const std::string& m)
{
    std::cerr << m << '\n';
}
