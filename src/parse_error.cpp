#include <Parse_Error.hpp>

Parse_Error::Parse_Error(int line_number, std::string expression)
    : location(nullptr, line_number, 0), expression(expression)
{
}

void Parse_Error::print_spaces_to_column(int column)
{
    for (int i = 0; i < column; i++)
    {
        std::cerr << " ";
    }
}

void Parse_Error::print_error_marker_to_column(int column)
{
    for (int i = 0; i < 3; i++)
    {
        print_spaces_to_column(column);
        std::cerr << '^' << "\n";
    }
}
