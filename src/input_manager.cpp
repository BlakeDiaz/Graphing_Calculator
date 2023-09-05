#include "Input_Manager.hpp"
#include "Calculator.hpp"
#include <iostream>

/**
 * Processes any input from the user.
 *
 * @param user_function_map An unordered map associating each UserFunction's identifier to the UserFunction itself.
 * @param user_functions A vector containing unordered sets of identifiers for UserFunctionss for each number of dependencies that a UserFunction can have.
 * @param expression The expression provided by the user.
 */
void Input_Manager::process_input(std::unordered_map<char, UserFunction>& user_function_map, std::vector<std::unordered_set<char>>& user_functions, std::string expression)
{
    Calculator::ExpressionType expression_type = Calculator::identify_expression(expression);
    std::string formatted_expression = Calculator::format_expression(user_function_map, expression);

    switch (expression_type)
    {
        case Calculator::SOLVABLE_EXPRESSION:
        {
            std::cout << "Formatted Expression: " << formatted_expression << std::endl;
            std::cout << "Solved Expression: " << Calculator::solve_expression(formatted_expression) << std::endl;
            break;
        }

        case Calculator::FUNCTION_DEFINITION:
        {
            UserFunction user_function(expression, formatted_expression, Calculator::locate_user_function_dependencies(user_function_map, expression));
            Input_Manager::process_user_function_input(user_function_map, user_functions, user_function);
            break;
        }
 

        default:
        {
            std::cout << "Error: Invalid Expression Type" << std::endl;
            break;
        }
    }
}

/**
 * Processes a UserFunction definition or re-definition from the user.
 *
 * @param user_function_map An unordered map associating each UserFunction's identifier to the UserFunction itself.
 * @param user_functions A vector containing unordered sets of identifiers for UserFunctionss for each number of dependencies that a UserFunction can have.
 * @param expression The expression provided by the user.
 */
void Input_Manager::process_user_function_input(std::unordered_map<char, UserFunction>& user_function_map, std::vector<std::unordered_set<char>>& user_functions, UserFunction& user_function)
{
    // Adding a new UserFunction
    if (!user_function_map.contains(user_function.identifier))
    {
        Input_Manager::add_user_function(user_function_map, user_functions, user_function);

        return;
    }

    // Verify whether the UserFunction has been updated
    UserFunction& old_user_function = user_function_map.at(user_function.identifier);
    if (old_user_function.formatted_expression == user_function.formatted_expression)
    {
        return;
    }

    int old_number_of_dependencies = old_user_function.user_function_dependencies.size();

    // Remove the old UserFunction
    user_function_map.erase(user_function.identifier);
    user_functions[old_number_of_dependencies].erase(user_function.identifier);

    // Add the new UserFunction
    Input_Manager::add_user_function(user_function_map, user_functions, user_function);

    /*
     * Loop through each UserFunction with more dependencies than the now updated UserFunction in ascending order regarding the number of dependencies.
     */
    std::unordered_set<char> updated_user_functions;

    std::string new_formatted_expression;
    std::unordered_set<char> new_user_function_dependencies;

    for (int i = old_number_of_dependencies + 1; i < user_functions.size(); i++)
    {
        for (char current_user_function_identifier : user_functions[i])
        {
            UserFunction& current_user_function = user_function_map.at(current_user_function_identifier);
            // If the current UserFunction has the updated UserFunction as a dependency, update the current UserFunction.
            if (!current_user_function.user_function_dependencies.contains(user_function.identifier))
            {
                continue;
            }

            user_function_map.erase(current_user_function_identifier);
            user_function_map.emplace(current_user_function_identifier, UserFunction(user_function_map, current_user_function.expression));
            
            // We temporarily store any updated UserFunctions in a seperate set to avoid repeatedly updating the same UserFunction
            user_functions[i].erase(current_user_function_identifier);
            updated_user_functions.emplace(current_user_function_identifier);
        }
    }

    // We now insert each UserFunction at its proper location according to how many dependencies it has
    for (char current_user_function_identifier : updated_user_functions)
    {
        UserFunction& current_user_function = user_function_map.at(current_user_function_identifier);
        user_functions[current_user_function.user_function_dependencies.size()].emplace(current_user_function_identifier);
    }
}

/**
 * Adds a UserFunction to the map of UserFunctions and the vector of unordered sets of UserFunction identifiers.
 *
 * @param user_function_map An unordered map associating each UserFunction's identifier to the UserFunction itself.
 * @param user_functions A vector containing unordered sets of identifiers for UserFunctionss for each number of dependencies that a UserFunction can have.
 */
void Input_Manager::add_user_function(std::unordered_map<char, UserFunction>& user_function_map, std::vector<std::unordered_set<char>>& user_functions, UserFunction& user_function)
{
    user_function_map.emplace(user_function.identifier, user_function);
        
    // Expand our list of UserFunctions at each number of dependencies if we need to.
    if (user_functions.size() <= user_function.user_function_dependencies.size())
    {
        for (int i = user_functions.size(); i <= user_function.user_function_dependencies.size(); i++)
        {
            user_functions.push_back(std::unordered_set<char>());
        }
    }
    // Add the UserFunction to our list at the correct amount of dependencies.
    user_functions[user_function.user_function_dependencies.size()].emplace(user_function.identifier);
}
