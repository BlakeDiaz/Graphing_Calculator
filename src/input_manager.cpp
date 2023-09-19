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

/**
 * Processes any input from the user.
 *
 * @param user_function_map An unordered map associating each User_Function's identifier to the User_Function itself.
 * @param user_functions A vector containing unordered sets of identifiers for User_Functionss for each number of dependencies that a User_Function can have.
 * @param expression The expression provided by the user.
 */
std::optional<std::string> Input_Manager::process_input(std::unordered_map<char, User_Function>& user_function_map, std::vector<std::unordered_set<char>>& user_functions, std::string expression)
{
    Calculator::ExpressionType expression_type = Calculator::identify_expression(expression);
    std::string formatted_expression = Calculator::format_expression(user_function_map, expression);

    switch (expression_type)
    {
        case Calculator::SOLVABLE_EXPRESSION:
        {
            double result =  Calculator::solve_expression(formatted_expression);
            return std::optional<std::string>(std::to_string(result));
        }

        case Calculator::FUNCTION_DEFINITION:
        {
            User_Function user_function(expression, formatted_expression, Calculator::locate_user_function_dependencies(expression));
            Input_Manager::process_user_function_input(user_function_map, user_functions, user_function);
            break;
        }

        default:
        {
            std::cout << "Error: Invalid Expression Type" << std::endl;
            break;
        }
    }

    return std::optional<std::string>();
}

/**
 * Processes a User_Function definition or re-definition from the user.
 *
 * @param user_function_map An unordered map associating each User_Function's identifier to the User_Function itself.
 * @param user_functions A vector containing unordered sets of identifiers for User_Functionss for each number of dependencies that a User_Function can have.
 * @param expression The expression provided by the user.
 */
void Input_Manager::process_user_function_input(std::unordered_map<char, User_Function>& user_function_map, std::vector<std::unordered_set<char>>& user_functions, User_Function& user_function)
{
    // Adding a new User_Function
    if (!user_function_map.contains(user_function.identifier))
    {
        Input_Manager::add_user_function(user_function_map, user_functions, user_function);

        return;
    }

    // Verify whether the User_Function has been updated
    User_Function& old_user_function = user_function_map.at(user_function.identifier);
    if (old_user_function.formatted_expression == user_function.formatted_expression)
    {
        return;
    }

    int old_number_of_dependencies = old_user_function.user_function_dependencies.size();

    // Remove the old User_Function
    user_function_map.erase(user_function.identifier);
    user_functions[old_number_of_dependencies].erase(user_function.identifier);

    // Add the new User_Function
    Input_Manager::add_user_function(user_function_map, user_functions, user_function);

    /*
     * Loop through each User_Function with more dependencies than the now updated User_Function in ascending order regarding the number of dependencies.
     */
    std::unordered_set<char> updated_user_functions;

    std::string new_formatted_expression;
    std::unordered_set<char> new_user_function_dependencies;

    for (int i = old_number_of_dependencies + 1; i < user_functions.size(); i++)
    {
        for (char current_user_function_identifier : user_functions[i])
        {
            User_Function& current_user_function = user_function_map.at(current_user_function_identifier);
            // If the current User_Function has the updated User_Function as a dependency, update the current User_Function.
            if (!current_user_function.user_function_dependencies.contains(user_function.identifier))
            {
                continue;
            }

            user_function_map.erase(current_user_function_identifier);
            user_function_map.emplace(current_user_function_identifier, User_Function(user_function_map, current_user_function.expression));
            
            // We temporarily store any updated User_Functions in a seperate set to avoid repeatedly updating the same User_Function
            user_functions[i].erase(current_user_function_identifier);
            updated_user_functions.emplace(current_user_function_identifier);
        }
    }

    // We now insert each User_Function at its proper location according to how many dependencies it has
    for (char current_user_function_identifier : updated_user_functions)
    {
        User_Function& current_user_function = user_function_map.at(current_user_function_identifier);
        user_functions[current_user_function.user_function_dependencies.size()].emplace(current_user_function_identifier);
    }
}

/**
 * Adds a User_Function to the map of User_Functions and the vector of unordered sets of User_Function identifiers.
 *
 * @param user_function_map An unordered map associating each User_Function's identifier to the User_Function itself.
 * @param user_functions A vector containing unordered sets of identifiers for User_Functionss for each number of dependencies that a User_Function can have.
 */
void Input_Manager::add_user_function(std::unordered_map<char, User_Function>& user_function_map, std::vector<std::unordered_set<char>>& user_functions, User_Function& user_function)
{
    user_function_map.emplace(user_function.identifier, user_function);
        
    // Expand our list of User_Functions at each number of dependencies if we need to.
    if (user_functions.size() <= user_function.user_function_dependencies.size())
    {
        for (int i = user_functions.size(); i <= user_function.user_function_dependencies.size(); i++)
        {
            user_functions.push_back(std::unordered_set<char>());
        }
    }
    // Add the User_Function to our list at the correct amount of dependencies.
    user_functions[user_function.user_function_dependencies.size()].emplace(user_function.identifier);
}
