#pragma once
#include "formatter.tab.hpp"
// Give flex the prototype of yylex we want...
#define YY_DECL \
    fmt::parser::symbol_type fmtlex()
// ... and declare it for the parser's sake.
YY_DECL;
