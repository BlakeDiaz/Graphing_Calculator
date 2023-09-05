#include "Input_Manager.hpp"
#include <iostream>
#include <optional>
#include <string>
#include <vector>
#include <array>
#include <cmath>
#include <unordered_map>
#include <unordered_set>

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

    Input_Manager::process_input(user_function_map, user_functions, "f(x) = 5x + 4");
    Input_Manager::process_input(user_function_map, user_functions, "g(x) = 3 * f(x)");
    Input_Manager::process_input(user_function_map, user_functions, "3 + f(5)");
    Input_Manager::process_input(user_function_map, user_functions, "f(x) = 5x + 3");

    return 0;
}
