#include<iostream>
#include<experimental/filesystem>
#include<fstream>
#include<stdexcept>
#include<vector>
#include<string>
#include<thread>

#include "InputValidation.hpp"


namespace fs = std::experimental::filesystem;

void collectAllFiles(const std::string& dirName, std::vector<fs::directory_entry>& fillesInAllDirectories, std::size_t capacityToReserve = 1000)
{
    fillesInAllDirectories.reserve(capacityToReserve);
    
    try{
        for (auto const& path : fs::recursive_directory_iterator(dirName))
        {
            if(fs::is_regular_file(fs::status(path))){    
                fillesInAllDirectories.emplace_back(std::move(path));
            }
        }
    }
    catch(fs::filesystem_error& e)
    {
      std::cout << "Unable to access file." << std::endl;
    }
}

void callculateNumberOfLines(const std::vector<fs::directory_entry>& fillesInAllDirectories)
{
    unsigned int numberOfLines = 0;
    std::string line;

    for (auto pathToFile : fillesInAllDirectories)
    {
        std::cout << pathToFile << std::endl;
        std::ifstream file(pathToFile.path());

        while(std::getline(file, line))
        {
            numberOfLines++;
        }

        std::cout<< "Numer of lines in a file: " << numberOfLines << std::endl;
        numberOfLines = 0;
    }
}




int main(int argc, char** argv)
{      
    std::vector<fs::directory_entry> fillesInAllDirectories;
    auto dirName = validateInput(argc, argv);
    collectAllFiles(dirName, fillesInAllDirectories);
    callculateNumberOfLines(fillesInAllDirectories);
}