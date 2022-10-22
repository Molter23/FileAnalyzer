#pragma once

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

namespace fs = std::experimental::filesystem;

void callculateNumberOfLines(const DataWrapper& data, Statistic& statistics, unsigned int start,  unsigned int end);
void collectAllFiles(const std::string& dirName, DataWrapper& data, Statistic& statistics,  std::size_t capacityToReserve = 1000);
unsigned int calculateNumberOfThreads(unsigned int requiredNumberOfThreads);
void startCounting(const DataWrapper& data, Statistic& statistics, unsigned int requiredNumberOfThreads = 4);
