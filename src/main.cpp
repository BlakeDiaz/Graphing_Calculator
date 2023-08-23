#include <iostream>
#include <optional>
#include <string>
#include <vector>
#include <array>
#include <cmath>
#include <unordered_map>
#include <unordered_set>
#include "Calculator.hpp"

void add_user_function(std::unordered_map<char, UserFunction>& user_function_map, std::vector<std::unordered_set<char>>& user_functions, UserFunction& user_function);
void process_user_function_input(std::unordered_map<char, UserFunction>& user_function_map, std::vector<std::unordered_set<char>>& user_functions, UserFunction& user_function);

std::ostream& operator<<(std::ostream& out, UserFunction const& user_function)
{
    out << "Identifier: " << user_function.identifier << "; ";
    out << "Variable: " << user_function.variable << "; ";
    out << "Expression: " << user_function.expression << "; ";
    out << "Formatted Expression: " << user_function.formatted_expression << "; ";
    out << "Number of Dependencies: " << user_function.user_function_dependencies.size() << "; ";

    return out;
}

/** 
 * Called by yyparse on error
 *
 * @param s Error message.
 */
void yyerror(char const *s)
{
    std::cout << s << std::endl;
}

/**
 * Processes any input from the user.
 *
 * @param user_function_map An unordered map associating each UserFunction's identifier to the UserFunction itself.
 * @param user_functions A vector containing unordered sets of identifiers for UserFunctionss for each number of dependencies that a UserFunction can have.
 * @param expression The expression provided by the user.
 */
void process_input(std::unordered_map<char, UserFunction>& user_function_map, std::vector<std::unordered_set<char>>& user_functions, std::string expression)
{
    auto&&[formatted_expression, possible_user_function] = Calculator::format_expression(user_function_map, expression);

    std::cout << "Is a function: " << (possible_user_function.has_value() ? "True" : "False") << std::endl;
    
    if (possible_user_function.has_value())
    {
        std::cout << possible_user_function.value() << std::endl;;
        process_user_function_input(user_function_map, user_functions, possible_user_function.value());
    }
    else
    {
        std::cout << "Formatted Expression: " << formatted_expression << std::endl;
        std::cout << "Solved Expression: " << Calculator::solve_expression(formatted_expression) << std::endl;
    }
}

/**
 * Processes a UserFunction definition or re-definition from the user.
 *
 * @param user_function_map An unordered map associating each UserFunction's identifier to the UserFunction itself.
 * @param user_functions A vector containing unordered sets of identifiers for UserFunctionss for each number of dependencies that a UserFunction can have.
 * @param expression The expression provided by the user.
 */
void process_user_function_input(std::unordered_map<char, UserFunction>& user_function_map, std::vector<std::unordered_set<char>>& user_functions, UserFunction& user_function)
{
    // Adding a new UserFunction
    if (!user_function_map.contains(user_function.identifier))
    {
        add_user_function(user_function_map, user_functions, user_function);

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
    add_user_function(user_function_map, user_functions, user_function);

    /*
     * Loop through each UserFunction with more dependencies than the now updated UserFunction in ascending order regarding the number of dependencies.
     */
    std::unordered_set<char> updated_user_functions;

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

            auto&&[formatted_expression, possible_user_function] = Calculator::format_expression(user_function_map, current_user_function.expression);
            user_function_map.erase(current_user_function_identifier);
            user_function_map.emplace(current_user_function_identifier, possible_user_function.value());
            
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
void add_user_function(std::unordered_map<char, UserFunction>& user_function_map, std::vector<std::unordered_set<char>>& user_functions, UserFunction& user_function)
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

/**
 * Main function.
 *
 * @param argc Number of command line arguments.
 * @param argv List of command line arguments.
 */
int main(int argc, char const* argv[])
{
    std::unordered_map<char, UserFunction> user_function_map;

    /*
     * The vector will contain unordered sets for each amount of dependencies that a UserFunction can have.
     * This means that whenever a UserFunction is updated, the sets containing all of the UserFunctions with more dependencies
     * than the updated UserFunction (the only ones that potentially need to be updated) can easily be searched through.
     */
    std::vector<std::unordered_set<char>> user_functions;

    process_input(user_function_map, user_functions, "f(x) = 5x + 4");
    process_input(user_function_map, user_functions, "g(x) = 3 * f(x)");
    process_input(user_function_map, user_functions, "3 + f(5)");
    process_input(user_function_map, user_functions, "f(x) = 5x + 3");

    return 0;
}
