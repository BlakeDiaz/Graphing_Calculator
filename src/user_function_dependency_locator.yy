/* User Function Dependency Locator*/

%skeleton "lalr1.cc" // C++
%require "3.8.2"
%header

%define api.token.raw

%define api.prefix {ufdl}
%define api.token.constructor
%define api.value.type variant
%define parse.assert

%{
  #include <iostream>
  void ufdlerror(char const *);
  extern int yylineno;
%}

// Used to simplify composite functions.
%parse-param { std::unordered_map<char, User_Function>& user_function_map }
%parse-param { std::unordered_set<char>& user_function_dependencies }

// Enable run-time traces (yydebug)
%define parse.trace
%define parse.error detailed
%define parse.lac full

%code requires
{
  #include <unordered_map>
  #include <set>
  #include "User_Function.hpp"
}

%code
{
    #include "ufdllex.hpp"
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

%token NUMBER // Double precision number
%token <std::string> VARIABLE // User Function Identifier ('f', 'g', etc.)
%token FUNCTION // Function (sin, cos, etc.)
%token USER_FUNCTION_ASSIGNMENT // User-created function assignment (e.g. f(x)=...)
%nterm implicit_multiplication_expression
%nterm expression

%precedence VARIABLE 
%left "-" "+"
%left "*" "/"
%precedence NEGATIVE_SIGN // Unary minus operator
%right "^"      // Exponent operator
%nonassoc "(" ")"

%% /* The grammar follows. */
input:
  %empty
| input line
;

line:
  "\n"
| USER_FUNCTION_ASSIGNMENT expression "\n"
| error "\n"                                { yyerrok; }
;

implicit_multiplication_expression:
  VARIABLE
| FUNCTION "(" expression ")"
| VARIABLE "(" expression ")"
{
    // If this is a function call, update our list of user function dependencies.
    char identifier = $1[0];
    if (user_function_map.contains(identifier))
    {
        const User_Function& user_function = user_function_map.at(identifier);
        user_function_dependencies.insert(user_function.identifier);
        user_function_dependencies.insert(user_function.user_function_dependencies.begin(),
                                          user_function.user_function_dependencies.end());
    }
}
| "(" expression ")"
| implicit_multiplication_expression VARIABLE
| implicit_multiplication_expression FUNCTION "(" expression ")"
| implicit_multiplication_expression VARIABLE "(" expression ")"
{
    // If this is a function call, update our list of user function dependencies.
    char identifier = $2[0];
    if (user_function_map.contains(identifier))
    {
        const User_Function& user_function = user_function_map.at(identifier);
        user_function_dependencies.insert(user_function.identifier);
        user_function_dependencies.insert(user_function.user_function_dependencies.begin(),
                                          user_function.user_function_dependencies.end());
    }
}
| implicit_multiplication_expression "(" expression ")"

expression:
  NUMBER
| implicit_multiplication_expression
| NUMBER implicit_multiplication_expression
| expression "+" expression
| expression "-" expression
| expression "*" expression
| expression "/" expression
| "-" expression  %prec NEGATIVE_SIGN
| expression "^" expression
/* End of grammar. */
%%
void ufdl::parser::error(const std::string& m)
{
    std::cerr << m << " Line: " << yylineno << '\n';
}
