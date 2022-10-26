#include<iostream>
#include<experimental/filesystem>
#include<fstream>
#include<stdexcept>
#include<vector>
#include<string>
#include<thread>

#include "InputValidation.hpp"
#include "Statistic.hpp"
#include "DataWrapper.hpp"
#include "Analyzer.hpp"

namespace fs = std::experimental::filesystem;

void callculateNumberOfLines(const DataWrapper& data, Statistic& statistics, unsigned int start,  unsigned int end)
{
    unsigned int numberOfLines = 0;
    std::string line;

    
    for (int i = start; i < end; i++)
    {
        std::ifstream file(data.fillesInAllDirectories[i].path());

        while(std::getline(file, line))
        {
            numberOfLines++;
        }

        statistics.numberOfLines.fetch_add(numberOfLines);

        numberOfLines = 0;
    }
}

void collectAllFiles(const std::string& dirName, DataWrapper& data, Statistic& statistics,  std::size_t capacityToReserve)
{
    data.fillesInAllDirectories.reserve(capacityToReserve);
    
    for (auto const& path : fs::recursive_directory_iterator(dirName, std::experimental::filesystem::v1::directory_options::skip_permission_denied))
    {
         if(fs::is_regular_file(fs::status(path))){    
            data.fillesInAllDirectories.emplace_back(std::move(path));
        }
    }

    statistics.numberOfDiretories = data.fillesInAllDirectories.size();
    
}

unsigned int calculateNumberOfThreads(unsigned int requiredNumberOfThreads)
{
    unsigned int numberOfPhysicalThread = std::thread::hardware_concurrency();
    unsigned int numberOfThreads = std::min(requiredNumberOfThreads, numberOfPhysicalThread);
}

void startCounting(const DataWrapper& data, Statistic& statistics, unsigned int requiredNumberOfThreads)
{
    unsigned int numberOfThreads = calculateNumberOfThreads(requiredNumberOfThreads);

    std::vector<std::thread> threads(numberOfThreads);

    unsigned int blockSize = (numberOfThreads + data.fillesInAllDirectories.size() - 1)/ numberOfThreads; //hack to make ceil with int type
    unsigned int start = 0, end = blockSize;

    for (int i = 0; i < numberOfThreads; i++)
    {
        threads[i] = std::thread(callculateNumberOfLines, std::ref(data), std::ref(statistics), start, end);

        start = end;
        end += blockSize;
        
        if(end > data.fillesInAllDirectories.size())
            end = data.fillesInAllDirectories.size();
    }
    
    for (std::thread& thread : threads)
        thread.join();
}