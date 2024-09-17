#pragma once

// Flex expects fmtlex to be defined in the macro YY_DECL
#define YY_DECL fmt::parser::symbol_type fmtlex(Parse_Error& parse_error)
