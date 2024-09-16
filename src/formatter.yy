/* Formatter for mathematical expressions to make them easier to parse. */

%skeleton "lalr1.cc" // C++
%require "3.8.2"
%header

%locations

%define api.prefix {fmt}

%define api.token.raw
%define api.token.constructor

%define api.value.type variant

%define api.location.type { ufdl::location }

%define parse.error custom
%define parse.assert

%{
  #include <iostream>
  #include <sstream>
%}

%param { Parse_Error& parse_error }
%parse-param { std::unordered_map<char, User_Function>& user_function_map }
%parse-param { std::string& result }

// Enable run-time traces (yydebug)
%define parse.trace

%code requires
{
  #include <unordered_map>
  #include <set>
  #include <Parse_Error.hpp>
  #include "User_Function.hpp"
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
| error                                     { YYABORT; }
;

implicit_multiplication_expression:
  VARIABLE                                                          { $$ = "(" + $1 + ")";                                                                                              }
| FUNCTION "(" expression ")"                                       { $$ = $1 + "(" + $3 + ")";                                                                                         }
| VARIABLE "(" expression ")"
{
    // If this is a function call, add the result of that call to our expression
    if (user_function_map.contains($1[0]))
    {
        $$ = "(" + user_function_map.at($1[0]).call($3) + ")";
    }
    // Otherwise, treat the grammar as implicit multiplication between a variable and an expression wrapped in parentheses.
    else
    {
        $$ = "(" + $1 + ")*" + "(" + $3 + ")";
    }
}
| "(" expression ")"                                                { $$ = "(" + $2 + ")";                                                                                              }
| implicit_multiplication_expression VARIABLE                       { $$ = $1 + "*" + "(" + $2 + ")";                                                                                   }
| implicit_multiplication_expression FUNCTION "(" expression ")"    { $$ = $1 + "*" + $2 + "(" + $4 + ")";                                                                              }
| implicit_multiplication_expression VARIABLE "(" expression ")"
{ 
    // If this is a function call, add the result of that call to our expression
    if (user_function_map.contains($2[0]))
    {
        $$ = $1 + "*" + "(" + user_function_map.at($2[0]).call($4) + ")";
    }
    // Otherwise, treat the grammar as implicit multiplication between a variable and an expression wrapped in parentheses.
    else
    {
        $$ = $1 + "*(" + $2 + ")*" + "(" + $4 + ")";
    }
}
| implicit_multiplication_expression "(" expression ")"             { $$ = $1 + "*" + "(" + $3 + ")";                                                                                   }

expression:
  NUMBER                                    { $$ = $1;                   }
| implicit_multiplication_expression        { $$ = $1;                   }
| NUMBER implicit_multiplication_expression { $$ = $1 + "*" + $2;        }
| expression "+" expression                 { $$ = $1 + "+" + $3;        }
| expression "-" expression                 { $$ = $1 + "-" + $3;        }
| expression "*" expression                 { $$ = $1 + "*" + $3;        }
| expression "/" expression                 { $$ = $1 + "/" + $3;        }
| "-" expression  %prec NEGATIVE_SIGN       { $$ = "-" + $2;             }
| expression "^" expression                 { $$ = $1 + "^" + $3;        }
;
/* End of grammar. */
%%
void fmt::parser::error(const location_type& location, const std::string& message)
{
    std::stringstream message_stream;

    int beginning_column = location.begin.column;
    message_stream << parse_error.expression << '\n';
    Parse_Error::print_error_marker_to_column(message_stream, beginning_column);
    message_stream << "Error on column " << beginning_column + 1 << "\n" << message;

    parse_error.message = message_stream.str();
    parse_error.is_error = true;
}
void fmt::parser::report_syntax_error(const context& error_context) const
{
    std::stringstream message_stream;

    location_type current_location = error_context.location();
    int beginning_column = current_location.begin.column;
    int ending_column = current_location.end.column;
    int symbol_length = ending_column - beginning_column;

    message_stream << parse_error.expression << '\n';
    Parse_Error::print_error_marker_to_column(message_stream, beginning_column);

    message_stream << "Syntax Error on column " << beginning_column + 1 << "\nUnexpected token: ";
    message_stream << fmt::parser::symbol_name(error_context.token()) << '\n';
    message_stream << "Expected token: ";

    symbol_kind_type expected_tokens[parser::YYNTOKENS];
    for (int i = 0; i < parser::YYNTOKENS; i++)
    {
        expected_tokens[i] = symbol_kind::S_YYEMPTY;
    }
    int success = error_context.expected_tokens(expected_tokens, parser::YYNTOKENS);

    if (expected_tokens[0] == symbol_kind::S_YYEMPTY)
    {
        message_stream << '\n' << "Something broke" << std::endl;
        return;
    }

    for (int i = 0; i < parser::YYNTOKENS - 1 && expected_tokens[i] != symbol_kind::S_YYEMPTY; i++)
    {
        message_stream << parser::symbol_name(expected_tokens[i]);
        if (expected_tokens[i + 1] != symbol_kind::S_YYEMPTY)
        {
            message_stream << ", ";
        }
    }

    parse_error.message = message_stream.str();
    parse_error.is_error = true;
}
