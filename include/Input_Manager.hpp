#include "UserFunction.hpp"
#include <unordered_map>
#include <unordered_set>
#include <vector>

class Input_Manager
{
public:
    static void process_input(std::unordered_map<char, UserFunction>& user_function_map, std::vector<std::unordered_set<char>>& user_functions, std::string expression);
private:
    static void process_user_function_input(std::unordered_map<char, UserFunction>& user_function_map, std::vector<std::unordered_set<char>>& user_functions, UserFunction& user_function);
    static void add_user_function(std::unordered_map<char, UserFunction>& user_function_map, std::vector<std::unordered_set<char>>& user_functions, UserFunction& user_function);
};
