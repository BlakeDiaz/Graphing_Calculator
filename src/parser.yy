/* Calculator with support for basic operations as well as functions such as "sin" and "cos". */

%skeleton "lalr1.cc" // C++
%require "3.8.2"
%header

%locations

%define api.token.raw
%define api.token.constructor

%define api.value.type variant

%define api.location.type { ufdl::location }

%define parse.error custom
%define parse.assert

%{
  #include <iostream>
  #include <cmath>
%}

%code requires
{
  #include "Function.hpp" // Includes func_map variable, and Function type
  #include <Parse_Error.hpp>
  #include <map>
}

%param { Parse_Error& parse_error }
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
| error             { YYABORT; }
;

expression:
  NUMBER                                { $$ = $1;          }
| FUNCTION "(" expression ")"           { $$ = $1.ptr($3);  }
| expression "+" expression             { $$ = $1 + $3;     }
| expression "-" expression             { $$ = $1 - $3;     }
| expression "*" expression             { $$ = $1 * $3;     }
| expression "/" expression             {
                                            if ($3 == 0)
                                            {
                                                throw yy::parser::syntax_error(@3, "Divide-by-zero error");
                                                $$ = 0;
                                            }
                                            else
                                            {
                                                $$ = $1 / $3;
                                            }
                                        }
| "-" expression  %prec NEGATIVE_SIGN   { $$ = -$2;         }
| expression "^" expression             { $$ = pow($1, $3); }
| "(" expression ")"                    { $$ = $2;          }
;
/* End of grammar. */
%%
void yy::parser::error(const location_type& location, const std::string& message)
{
    int beginning_column = location.begin.column;
    std::cerr << parse_error.expression << '\n';
    Parse_Error::print_error_marker_to_column(beginning_column);
    std::cerr << "Error on line 1, column " << beginning_column << "\n" << message << std::endl;
}
void yy::parser::report_syntax_error(const context& error_context) const
{
    location_type current_location = error_context.location();
    int beginning_column = current_location.begin.column;
    int ending_column = current_location.end.column;
    int symbol_length = ending_column - beginning_column;

    std::cerr << parse_error.expression << '\n';
    Parse_Error::print_error_marker_to_column(beginning_column);

    std::cerr << "Syntax Error on line 1, column " << beginning_column << "\nUnexpected token: ";
    std::cerr << yy::parser::symbol_name(error_context.token()) << '\n';
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
