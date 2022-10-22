#include<iostream>
#include<experimental/filesystem>
#include<fstream>
#include<stdexcept>
#include<vector>
#include<string>
#include<thread>

#include "InputValidation.hpp"
#include "DataWrapper.cpp"

namespace fs = std::experimental::filesystem;

void callculateNumberOfLines(DataWrapper& data, unsigned int start,  unsigned int end)
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

        data.numberOfLines += numberOfLines;

        numberOfLines = 0;
    }
}

void collectAllFiles(const std::string& dirName, DataWrapper& data, std::size_t capacityToReserve = 1000)
{
    data.fillesInAllDirectories.reserve(capacityToReserve);
    
    try{
        for (auto const& path : fs::recursive_directory_iterator(dirName))
        {
            if(fs::is_regular_file(fs::status(path))){    
                data.fillesInAllDirectories.emplace_back(std::move(path));
            }
        }
        data.numberOfDiretories = data.fillesInAllDirectories.size();
    }
    catch(fs::filesystem_error& e)
    {
      std::cout << "Unable to access file." << std::endl;
    }
}

std::ostream& operator<<(std::ostream& os, const DataWrapper& obj)
{
    return os << "Number of directories: " << obj.numberOfDiretories << std::endl << "Number of lines: " << obj.numberOfLines << std::endl;
}

DataWrapper DataWrapper::_dwInstance;



int main(int argc, char** argv)
{      
    DataWrapper& data = DataWrapper::get();
    
    auto dirName = validateInput(argc, argv);
    collectAllFiles(dirName, data);
    callculateNumberOfLines(data, 0, data.fillesInAllDirectories.size());
    std::cout<< data;
  

}