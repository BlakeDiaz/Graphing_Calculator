# CTD-84 Graphing Calculator
A desktop graphing calculator inspired by Desmos.

## Features
- Basic arithmetic, exponents
- Basic functions - `sqrt`, `log`, `ln`
- Trigonometric functions - `sin`, `asin`, etc.
- User-defined functions - e.g. `f(x) = x + 5`
    - Supports up to 52 functions - one for each ASCII letter in upper and lowercase
- Implicit multiplication - e.g. `5(3+4)`
- Composite functions - e.g. `a(x) = b(c(x))`
- Customizable graph colors in ARGB
- Customizable graph window range

## Gallery
<img width="958" alt="Graphing Calculator Example 1" src="https://github.com/user-attachments/assets/2e4f3e04-c660-44af-aa7c-818d17caa4d2">
<img width="958" alt="Graphing Calculator Example 2" src="https://github.com/user-attachments/assets/c7ae0370-c57f-4fa6-a340-d2c327df6a9c">

## Build Instructions
1. Install flex, Bison, and CMake
2. Add flex and Bison to your PATH
3. Clone the repository
4. Build the project with CMake

## Technical Explanation
The calculator largely consists of two halves - the actual calculation, and the ui surrounding it.
Changes in the UI are processed once the `Update` button is pressed.
Once the button is pressed, a few things happen.

First, the graph window (the minimum and maximum values of the x and y axes) is updated.
Second, the axis settings (whether the x and y axes and their associated markers are displayed) are updated.
Third, each item in the function table is processed.

If a given item is determined to be a solvable expression, we skip it for now.
If it's a function definition, we figure out what other user functions it depends on and store that information for later.
After that, we create a user function map.

This map associates the identifier of a user function (i.e. the `f` in `f(x)= 5x + 4`) with the function itself to allow for easy lookups later.
This is also where we check to see if the dependencies of our user functions can be resolved, and where we create the user function objects themselves.

When we create user functions, we format the bodies of their expressions to make them easier to evaluate at different points.
The formatting involves a few steps.
First, `*` symbols are inserted where implicit multiplication occurs e.g. changing `5(3+4)` to `5*(3+4)`.
Second, parentheses are placed around the function's variable.
This makes it easier for us to repalce the function's variable with the point the function is being evaluated at.
Finally, calls to other user functions are replaced with their formatted bodies.

Once the map is created, we once again loop through each item in our function table now that our user functions have been created and indexed.
If it's a solvable expression, we replace each user function call with the formatted body of our user function and then solve the expression.

After finishing this, the final step is to update the graph being displayed.
This involves taking each user function's body and evaluating it at thousands of points between the minimum and maximum values of the x-axis.
Finally, we render each user function's points with its associated color.

Three parsers (and their lexers) are used to help process input.
First, the dependency locator parser is used to figure out what other user-defined functions our given function depends on.
Second, the formatter parser is used to format user functions and expressions.
Finally, the solver parser is used to evaluate expressions as well as user functions at specific points.
