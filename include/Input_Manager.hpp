#include "User_Function.hpp"
#include <unordered_map>
#include <unordered_set>
#include <optional>
#include <vector>

class Input_Manager
{
public:
    static std::unordered_map<char, User_Function> create_user_function_map(std::vector<std::tuple<std::string, std::unordered_set<char>>>& new_user_function_expressions);
    static std::optional<std::string> process_input(std::unordered_map<char, User_Function>& user_function_map, std::vector<std::unordered_set<char>>& user_functions, std::string expression);
private:
    static void process_user_function_input(std::unordered_map<char, User_Function>& user_function_map, std::vector<std::unordered_set<char>>& user_functions, User_Function& user_function);
    static void add_user_function(std::unordered_map<char, User_Function>& user_function_map, std::vector<std::unordered_set<char>>& user_functions, User_Function& user_function);
};
