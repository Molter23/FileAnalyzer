#include<iostream>
#include<experimental/filesystem>
#include<fstream>
#include<stdexcept>

namespace fs = std::experimental::filesystem;

void usage(const std::string& programName)
{
    std::cout <<"Usage: " << std::endl << std::endl;
    std::cout << "\t" << programName << " [path to directory]" << std::endl << std::endl;
}

void validateLengthOfInput(int argc)
{
    if(argc > 2)
        throw std::invalid_argument("Too many arguments spcified.");
        
    if(argc == 1)
        throw std::invalid_argument("Path not spcified.");

}

void validatePath(const std::string& dirName)
{
    if(!fs::is_directory(fs::status(dirName)))
        throw std::invalid_argument("Given argument is not a path to directory.");
}

std::string validateInput(int argc, char** argv)
{
    try{
        validateLengthOfInput(argc);

        std::string dirName = argv[1];
        validatePath(dirName);

    } catch(const std::invalid_argument& e) {   
        std::cout << e.what() << std::endl;
        std::string programName = argv[0];
        usage(programName);
        std::cerr << "Wrong input" << std::endl;
        exit(EXIT_FAILURE);
    }       
    
    return argv[1];
}