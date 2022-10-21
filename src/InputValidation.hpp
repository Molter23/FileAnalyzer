
#pragma once

#include <iostream>

void usage(const std::string& programName);
void validateLengthOfInput(int argc);
void validatePath(const std::string& dirName);
std::string validateInput(int argc, char** argv);