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
        user_function_map.emplace('f', UserFunction('f', 'x', "f(x) = 5x + 4", "5*((x))+4", std::set<char>()));
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

TEST_F(CalculatorTestFixture, FormatExpression)
{
    EXPECT_STREQ(std::get<0>(Calculator::format_expression(user_function_map, "g(x) = 5x + 4")).c_str(), "5*((x))+4");
}

}
