#include "gtest/gtest.h"
#include "../src/InputValidation.hpp"

TEST(ValidationInputTests, TooMuchArgumentsShouldThrow)
{
   ASSERT_THROW(validateLengthOfInput(3), std::invalid_argument);
}

TEST(ValidationInputTests, PathNotSpecifiedShouldThrow)
{
   ASSERT_THROW(validateLengthOfInput(1), std::invalid_argument);
}

TEST(ValidationInputTests, CorrectNumberOfArgumentsShoulNotThrow)
{
   ASSERT_NO_THROW(validateLengthOfInput(2));
}

TEST(ValidationInputTests, IncorrectPathShouldThrow)
{ 
    ASSERT_THROW(validatePath("dasdsadasdasddba"), std::invalid_argument);
}

TEST(ValidationInputTests, CorrectPathShoulNotThrow)
{
   ASSERT_NO_THROW(validatePath("/"));
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

