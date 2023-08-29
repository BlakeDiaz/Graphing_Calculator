#include <algorithm>
#include <string>

/**
 * Removes whitespace from a string.
 * The original string is not modified.
 * Whitespace characters are determined by the std::isspace function.
 *
 * @param str The string that whitespace is removed from.
 * @return Copy of str without any whitespace characters.
 */
std::string remove_whitespace(std::string str)
{
    str.erase(std::remove_if(str.begin(), str.end(), [](unsigned char x) { return std::isspace(x); }), str.end());
    return str;
}
