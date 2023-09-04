#include "gtest/gtest.h"
#include "Calculator.hpp"
#include <cmath>

namespace {

class CalculatorTestFixture : public testing::Test
{
protected:
    std::unordered_map<char, UserFunction> user_function_map;

    void SetUp() override
    {
        user_function_map.emplace('f', UserFunction('f', 'x', "f(x) = 5x + 4", "5*((x))+4", std::unordered_set<char>()));
    }
};


TEST(CalculatorTest, FunctionMap)
{
    EXPECT_TRUE(Calculator::function_map.contains("sin"));
    EXPECT_TRUE(Calculator::function_map.contains("cos"));
    EXPECT_TRUE(Calculator::function_map.contains("tan"));
    EXPECT_TRUE(Calculator::function_map.contains("asin"));
    EXPECT_TRUE(Calculator::function_map.contains("acos"));
    EXPECT_TRUE(Calculator::function_map.contains("atan"));
    EXPECT_TRUE(Calculator::function_map.contains("log"));
    EXPECT_TRUE(Calculator::function_map.contains("ln"));
    EXPECT_TRUE(Calculator::function_map.contains("sqrt"));
}

TEST(CalculatorTest, IdentifyExpression)
{
    EXPECT_EQ(Calculator::identify_expression("f(x) = 5x + 4"), Calculator::FUNCTION_DEFINITION);
    EXPECT_EQ(Calculator::identify_expression("   g  ( x ) = \n x^3"), Calculator::FUNCTION_DEFINITION);
    EXPECT_EQ(Calculator::identify_expression("r(x)=19"), Calculator::FUNCTION_DEFINITION);
    EXPECT_EQ(Calculator::identify_expression("5+5"), Calculator::SOLVABLE_EXPRESSION);
    EXPECT_EQ(Calculator::identify_expression("sin(3) + 14f(2)"), Calculator::SOLVABLE_EXPRESSION);
    EXPECT_EQ(Calculator::identify_expression("f(g(l(11)) + 10^3)*log(5)"), Calculator::SOLVABLE_EXPRESSION);
}

TEST_F(CalculatorTestFixture, FormatExpression)
{
    EXPECT_STREQ(Calculator::format_expression(user_function_map, "g(x) = 5x + 4").c_str(), "5*(x)+4");
}

}
