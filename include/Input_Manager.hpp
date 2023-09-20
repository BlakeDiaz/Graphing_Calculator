#include "User_Function.hpp"
#include <unordered_map>
#include <unordered_set>
#include <optional>
#include <vector>
#include <QColor>

class Input_Manager
{
public:
    static std::unordered_map<char, User_Function> create_user_function_map(std::vector<std::tuple<std::string, std::unordered_set<char>, QColor>>& new_user_function_expressions);
};
