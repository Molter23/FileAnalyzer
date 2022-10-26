#include "gtest/gtest.h"
#include "../src/InputValidation.hpp"

#include<vector>

TEST(ValidationInputTests, TooMuchArgumentsShouldThrow)
{
   ASSERT_THROW(validateLengthOfInput(4), std::invalid_argument);
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
   std::vector<char*> argsVect = {strdup("prgram name"), strdup("something"), strdup("something")};

   ASSERT_EXIT(validateInput(argsVect.size(), argsVect.data()), ::testing::ExitedWithCode(1), "Wrong input");
}

TEST(ValidationInputTests, ValidateCorrectInputWithNumberOfThreads)
{
   std::vector<char*> argsVect = {strdup("prgram name"), strdup("/bin"), strdup("2")};

   auto [dirName, numberOfThreads] = validateInput(argsVect.size(), argsVect.data());

   ASSERT_EQ(dirName, "/bin");
   ASSERT_EQ(numberOfThreads, 2);
}

TEST(ValidationInputTests, ValidateCorrectInputWithoutNumberOfThreads)
{
   std::vector<char*> argsVect = {strdup("prgram name"), strdup("/bin") };

   auto [dirName, numberOfThreads] = validateInput(argsVect.size(), argsVect.data());

   ASSERT_EQ(dirName, "/bin");
   ASSERT_EQ(numberOfThreads, 4);
}

TEST(ValidationInputTests, NotANumberShouldThrow)
{
   ASSERT_THROW(validateNumberOfThreads("NaN"), std::invalid_argument);
}

TEST(ValidationInputTests, correctNumberShoulBeTrue)
{
   std::string number = "12";
   ASSERT_EQ(validateNumberOfThreads(number), 12);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

