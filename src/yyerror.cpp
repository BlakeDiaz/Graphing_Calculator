#include <iostream>

/**
 * Called by yyparse on error
 *
 * @param s Error message.
 */
void yyerror(char const* s)
{
    std::cout << s << std::endl;
}
