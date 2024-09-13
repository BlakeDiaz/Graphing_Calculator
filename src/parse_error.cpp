#include <Parse_Error.hpp>


Parse_Error::Parse_Error(int line_number, std::string expression)
    : location(nullptr, line_number, 0), expression(expression)
{
}
