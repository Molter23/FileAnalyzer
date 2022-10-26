#include<iostream>

#include "Analyzer.hpp"

int main(int argc, char** argv)
{      
    DataWrapper& data = DataWrapper::get();
    Statistic& statistics = Statistic::get();
    
    auto [dirName, numberOfThreads]  = validateInput(argc, argv);
    collectAllFiles(dirName, data, statistics);
    startCounting(data, statistics, numberOfThreads);
    std::cout << statistics;
}