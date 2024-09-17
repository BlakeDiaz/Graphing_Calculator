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

Input in the form of a user-defined function is put through three parsers (and their associated lexers).

First, a dependency locator to figure out what other user-defined functions our given function depends on.

Second, a formatter that expands composite functions to their base terms.

For example, if the two functions in the calculator were `f(x) = x + 2` and `g(x) = f(x)^2`, the formatter would expand `g(x)` internally to `g(x) = (x + 2)^2`.

The third parser evaluates the value of a function at a certain point, for example, `g(2)`.

This parser is run thousands of times in order to get enough points to display a graph of the function.
