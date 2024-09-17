#include <Parse_Error.hpp>

Parse_Error::Parse_Error(int row_number, std::string expression)
    : location(nullptr, row_number, 0), expression(expression), message(""), is_error(false)
{
}

void Parse_Error::print_spaces_to_column(std::stringstream& stream, int column)
{
    for (int i = 0; i < column; i++)
    {
        stream << " ";
    }
}

void Parse_Error::print_error_marker_to_column(std::stringstream& stream, int column)
{
    for (int i = 0; i < 3; i++)
    {
        print_spaces_to_column(stream, column);
        stream << '^' << "\n";
    }
}
