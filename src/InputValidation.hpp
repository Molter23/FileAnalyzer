
#pragma once

#include <iostream>
#include <utility>

void usage(const std::string& programName);
unsigned int validateLengthOfInput(unsigned int argc);
void validatePath(const std::string& dirName);
unsigned int validateNumberOfThreads(const std::string& numberOfThreads);
void errorMessage(const std::string& programName, const std::exception& e);
std::pair<std::string, unsigned int> validateInput(int argc, char** argv);