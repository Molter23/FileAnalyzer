#include<vector>
#include<thread>

#include "gtest/gtest.h"
#include "../src/InputValidation.hpp"
#include "../src/Analyzer.hpp"

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

TEST(ValidationInputTests, CorrectNumberShoulBeTrue)
{
   std::string number = "12";
   ASSERT_EQ(validateNumberOfThreads(number), 12);
}

TEST(AnalyzerTests, TooBigNumberOfThreadsPassed)
{
   unsigned int numberOfThreads = calculateNumberOfThreads(std::thread::hardware_concurrency() + 20);
   ASSERT_EQ(std::thread::hardware_concurrency(), numberOfThreads);
}

TEST(AnalyzerTests, NormalNumberOfThreadsPassed)
{
   ASSERT_EQ(calculateNumberOfThreads(1), 1);
}

TEST(AnalyzerTests, ResultShouldBeThreadIndependent)
{
   DataWrapper& data = DataWrapper::get();
   Statistic& statistics = Statistic::get();
    
   std::string dirName = "/bin";

   collectAllFiles(dirName, data, statistics);

   startCounting(data, statistics, 1);
   uint64_t resultForOneThread = statistics.numberOfLines.load();
   statistics.numberOfLines.store(0);

   startCounting(data, statistics, 2);
   uint64_t resultForTwoThreads = statistics.numberOfLines.load();
   statistics.numberOfLines.store(0);

   

   ASSERT_EQ(resultForOneThread, resultForTwoThreads);

   if (std::thread::hardware_concurrency()  > 4)    
   {
      startCounting(data, statistics, 3); 
      uint64_t resultForThreeThreads = statistics.numberOfLines.load();
      statistics.numberOfLines.store(0);

      startCounting(data, statistics, 4);
      uint64_t resultForFourThreads = statistics.numberOfLines.load(); 
      statistics.numberOfLines.store(0);

      ASSERT_EQ(resultForOneThread, resultForThreeThreads);
      ASSERT_EQ(resultForOneThread, resultForFourThreads);
   }

}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

