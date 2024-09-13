/* User Function Dependency Locator*/

%skeleton "lalr1.cc" // C++
%require "3.8.2"
%header

%locations

%define api.prefix {ufdl}

%define api.token.raw
%define api.token.constructor

%define api.value.type variant

%define api.location.file "../include/location.hpp"

%define parse.error custom

%{
  #include <iostream>
%}

// Used to simplify composite functions.
%param { Parse_Error& parse_error }
%parse-param { std::unordered_set<char>& user_function_dependencies }
%parse-param { const char variable }

%code requires
{
  #include <unordered_map>
  #include <set>
  #include <Parse_Error.hpp>
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
| error "\n"                                { YYABORT; }
;

implicit_multiplication_expression:
  VARIABLE
| FUNCTION "(" expression ")"
| VARIABLE "(" expression ")"
{
    // If this is a function call, update our list of user function dependencies.
    char identifier = $1[0];
    if (identifier != variable)
    {
        user_function_dependencies.emplace(identifier);
    }
}
| "(" expression ")"
| implicit_multiplication_expression VARIABLE
| implicit_multiplication_expression FUNCTION "(" expression ")"
| implicit_multiplication_expression VARIABLE "(" expression ")"
{
    // If this is a function call, update our list of user function dependencies.
    char identifier = $2[0];
    if (identifier != variable)
    {
        user_function_dependencies.emplace(identifier);
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
void print_spaces_to_column(int column)
{
    for (int i = 0; i < column; i++)
    {
        std::cerr << " ";
    }
}
void print_error_marker(int column)
{
    for (int i = 0; i < 3; i++)
    {
        print_spaces_to_column(column);
        std::cerr << '^' << "\n";
    }
}
void ufdl::parser::error(const location_type& location, const std::string& message)
{
    int beginning_column = location.begin.column;
    std::cerr << parse_error.expression << '\n';
    print_error_marker(beginning_column);
    std::cerr << "Error on line 1, column " << beginning_column << "\n" << message << std::endl;
}
void ufdl::parser::report_syntax_error(const context& error_context) const
{
    location_type current_location = error_context.location();
    int beginning_column = current_location.begin.column;
    int ending_column = current_location.end.column;
    int symbol_length = ending_column - beginning_column;

    std::cerr << parse_error.expression << '\n';
    print_error_marker(beginning_column);

    std::cerr << "Syntax Error on line 1, column " << beginning_column << "\nUnexpected token: ";
    std::cerr << ufdl::parser::symbol_name(error_context.token()) << '\n';
    std::cerr << "Expected token: ";

    symbol_kind_type expected_tokens[parser::YYNTOKENS];
    for (int i = 0; i < parser::YYNTOKENS; i++)
    {
        expected_tokens[i] = symbol_kind::S_YYEMPTY;
    }
    int success = error_context.expected_tokens(expected_tokens, parser::YYNTOKENS);

    if (expected_tokens[0] == symbol_kind::S_YYEMPTY)
    {
        std::cerr << '\n' << "Something broke" << std::endl;
        return;
    }

    for (int i = 0; i < parser::YYNTOKENS - 1 && expected_tokens[i] != symbol_kind::S_YYEMPTY; i++)
    {
        std::cerr << parser::symbol_name(expected_tokens[i]);
        if (expected_tokens[i + 1] != symbol_kind::S_YYEMPTY)
        {
            std::cerr << ", ";
        }
    }
    std::cerr << std::endl;
}
