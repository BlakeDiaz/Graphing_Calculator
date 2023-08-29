#pragma once

// Flex expects ufdllex to be defined in the macro YY_DECL
#define YY_DECL ufdl::parser::symbol_type ufdllex()
