#include<iostream>
#include<experimental/filesystem>
#include<fstream>
#include<stdexcept>
#include<vector>

#include "InputValidation.hpp"


namespace fs = std::experimental::filesystem;

void collectAllFiles(const std::string& dirName, std::size_t capacityToReserve = 1000)
{
    std::vector<fs::directory_entry> fillesInAllDirectories;
    fillesInAllDirectories.reserve(capacityToReserve);
    
    for (auto const& path : fs::recursive_directory_iterator(dirName))
    {
        if(fs::is_regular_file(fs::status(path))){    
            fillesInAllDirectories.emplace_back(std::move(path));
        }
    }
}


int main(int argc, char** argv)
{   
    auto dirName = validateInput(argc, argv);
    collectAllFiles(dirName);
}