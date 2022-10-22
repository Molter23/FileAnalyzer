#include<iostream>
#include<experimental/filesystem>
#include<fstream>
#include<stdexcept>
#include<vector>
#include<string>
#include<thread>

#include "Analyzer.hpp"


int main(int argc, char** argv)
{      
    DataWrapper& data = DataWrapper::get();
    Statistic& statistics = Statistic::get();
    
    auto dirName = validateInput(argc, argv);
    collectAllFiles(dirName, data, statistics);
    startCounting(data, statistics);
    std::cout<< statistics;
}