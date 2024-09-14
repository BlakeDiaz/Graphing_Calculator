#pragma once
#include <location.hpp>
#include <string>
#include <sstream>

struct Parse_Error
{
    ufdl::location location;
    std::string expression;
    std::string message;
    bool is_error;

    Parse_Error(int line_number, std::string expression);

    /**
    * Prints three ^ symbols on three lines at a given column.
    * 0 is the first column of a line.
    * For example, the given code:
    *   std::cout << "Hi there!\n";
    *   print_error_marker_to_column(4);
    *  Will give the output
    *   Hi there!
    *       ^
    *       ^
    *       ^
    *
    *  @param column Column markers are printed at.
    */
    static void print_error_marker_to_column(std::stringstream& stream, int column);
private:
    /**
     * Prints spaces up to, but not at, a given column.
     * 0 is the first column of a line.
     * For example, print_spaces_to_column(2) would print 2 spaces.
     *
     * @param column Column spaces are printed up to. Exclusive.
     */
    static void print_spaces_to_column(std::stringstream& stream, int column);
};
