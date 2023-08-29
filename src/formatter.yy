/* Formatter for mathematical expressions to make them easier to parse. */

%skeleton "lalr1.cc" // C++
%require "3.8.2"
%header

%define api.token.raw

%define api.prefix {fmt}
%define api.token.constructor
%define api.value.type variant
%define parse.assert

%{
  #include <iostream>
  void fmterror(char const *);
  extern int yylineno;
%}

// Used to simplify composite functions.
%parse-param { std::unordered_map<char, UserFunction>& user_function_map }
// Used later to create a UserFunction if the expression was a function declaration.
%parse-param { std::string& result }

// Enable run-time traces (yydebug)
%define parse.trace

%code requires
{
  #include <unordered_map>
  #include <set>
  #include "UserFunction.hpp"
}

%code
{
    #include "fmtlex.hpp"
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
| expression "\n"                           { result = $1; }
| USER_FUNCTION_ASSIGNMENT expression "\n"  { result = $2; }
| error "\n"                                { yyerrok;     }
;

implicit_multiplication_expression:
  VARIABLE                                                          { $$ += "(" + $1 + ")";                                                                                              }
| FUNCTION "(" expression ")"                                       { $$ += $1 + "(" + $3 + ")";                                                                                         }
| VARIABLE "(" expression ")"
{
    // If this is a function call, add the result of that call to our expression
    if (user_function_map.contains($1[0]))
    {
        $$ += user_function_map.at($1[0]).call($3);
    }
    // Otherwise, treat the grammar as implicit multiplication between a variable and an expression wrapped in parentheses.
    else
    {
        $$ += $1 + "(" + $3 + ")";
    }
}
| "(" expression ")"                                                { $$ += "(" + $2 + ")";                                                                                              }
| implicit_multiplication_expression VARIABLE                       { $$ += $1 + "*" + "(" + $2 + ")";                                                                                   }
| implicit_multiplication_expression FUNCTION "(" expression ")"    { $$ += $1 + "*" + $2 + "(" + $4 + ")";                                                                              }
| implicit_multiplication_expression VARIABLE "(" expression ")"
{ 
    // If this is a function call, add the result of that call to our expression
    if (user_function_map.contains($2[0]))
    {
        $$ += user_function_map.at($2[0]).call($4);
    }
    // Otherwise, treat the grammar as implicit multiplication between a variable and an expression wrapped in parentheses.
    else
    {
        $$ += $2 + "(" + $4 + ")";
    }
}
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
    std::cerr << m << " Line: " << yylineno << '\n';
}
