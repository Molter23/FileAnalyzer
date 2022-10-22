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

TEST(ValidationInputTests, ValidateInputExitCode)
{
   char* first_arg = "programName";
   char* second_arg = "path";
   char* third_arg = "somethingElse";

   char** argv = new char*;
   argv[0] = first_arg;
   argv[1] = second_arg; 
   argv[2] = third_arg;

   ASSERT_EXIT(validateInput(1,argv), ::testing::ExitedWithCode(1), "Wrong input");
}



int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

