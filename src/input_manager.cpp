#include "Input_Manager.hpp"
#include "Calculator.hpp"
#include "User_Function.hpp"
#include <iostream>
#include <unordered_map>
#include <tuple>

/**
 * Checks if a user function can be defined by checking if each of its dependencies are defined in the user_functions_map.
 *
 * @param user_function_map An unordered map associating each User_Function's identifier to the User_Function itself.
 * @param expression The expression representing a User_Function to potentially define.
 * @param dependencies An unordered set containing the identifiers of each direct user function dependency of the User_Function the expression represents.
 * @return true if a User_Function can be defined, otherwise returns false.
 */
static bool check_if_user_function_can_be_defined(const std::unordered_map<char, User_Function>& user_function_map, const std::string& expression, const std::unordered_set<char>& dependencies)
{
    for (char dependency : dependencies)
    {
        if (!user_function_map.contains(dependency))
        {
            return false;
        }
    }

    return true;
}

/**
 * Creates an unordered map associating each User_Function's identifier to the User_Function itself.
 *
 * @param new_user_function_expressions A list of tuples containing an expression reperesenting a User_Function, and an unordered set containing the identifiers of each direct
 *                                      user function dependency of the User_Function the expression represents.
 * @return An unordered map containing the User_Functions the list of expressions represent.
 */
std::unordered_map<char, User_Function> Input_Manager::create_user_function_map(std::vector<std::tuple<std::string, std::unordered_set<char>>>& new_user_function_expressions)
{
    /*
     * To assemble each User_Function, we need to have its dependencies assembled in the map first, so that we can replace its dependencies' function calls with its dependencies'
     * formatted expressions. This means that we have to assemble the User_Functions where each User_Function can only be assembled if its dependencies are already in the map.
     *
     */
    std::unordered_map<char, User_Function> user_function_map;
    for (int i = 0; i < new_user_function_expressions.size();)
    {
        auto&& [expression, dependencies] = new_user_function_expressions.at(i);
        if (dependencies.size() == 0)
        {
            user_function_map.emplace(User_Function::find_identifier(expression), User_Function(user_function_map, expression));
            new_user_function_expressions.erase(new_user_function_expressions.begin() + i);
        }
        else
        {
            i++;
        }
    }

    int previous_user_function_expression_length = new_user_function_expressions.size();
    bool invalid_dependency = false;
    bool user_function_can_be_defined = true;
    while (!new_user_function_expressions.empty())
    {
        for (int i = 0; i < new_user_function_expressions.size(); i++)
        {
            auto&& [expression, dependencies] = new_user_function_expressions.at(i);
            
            if (check_if_user_function_can_be_defined(user_function_map, expression, dependencies))
            {
                user_function_map.emplace(User_Function::find_identifier(expression), User_Function(user_function_map, expression));
                new_user_function_expressions.erase(new_user_function_expressions.begin() + i);
            }

            user_function_can_be_defined = true;
            
        }
        // If at least one function hasn't been added, then we can't continue, and the remaining functions' dependencies are invalid 
        if (new_user_function_expressions.size() >= previous_user_function_expression_length)
        {
            // TODO Handle the error with a pop-up or error section in the UI
            new_user_function_expressions.clear();
            invalid_dependency = true;
            break;
        }
    }

    // Handle error of invalid dependency
    if (invalid_dependency)
    {
        std::cerr << "Invalid Dependency" << std::endl;
    }

    return user_function_map;
}
