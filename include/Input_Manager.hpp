#include "User_Function.hpp"
#include <QColor>
#include <optional>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <User_Function_Map_Error.hpp>

class Input_Manager
{
  public:
    static std::tuple<std::unordered_map<char, User_Function>, User_Function_Map_Error> create_user_function_map(
        std::vector<std::tuple<std::string, std::unordered_set<char>, QColor, int>>& new_user_function_expressions, int number_of_rows);
};
