#include<iostream>
#include<experimental/filesystem>
#include<fstream>
#include<stdexcept>
#include<string>
#include<utility>

namespace fs = std::experimental::filesystem;

void usage(const std::string& programName)
{
    std::cout <<"Usage: " << std::endl << std::endl;
    std::cout << "\t" << programName << " [path to directory] <number of threads>" << std::endl << std::endl;
}

unsigned int validateLengthOfInput(unsigned int argc)
{    
    if(argc == 1)
        throw std::invalid_argument("Path not spcified.");

    if(argc > 3)
        throw std::invalid_argument("Too many arguments spcified.");
    
    return argc;
}

void validatePath(const std::string& dirName)
{
    if(!fs::is_directory(fs::status(dirName)))
        throw std::invalid_argument("Given argument is not a path to directory.");
}

unsigned int validateNumberOfThreads(const std::string& numberOfThreads)
{
    return std::stoi(numberOfThreads);
}

void errorMessage(const std::string& programName, const std::exception& e)
{
    std::cout << e.what() << std::endl;
    usage(programName);
    std::cerr << "Wrong input" << std::endl;
    exit(EXIT_FAILURE);
}

std::pair<std::string, unsigned int> validateInput(int argc, char** argv)
{
    unsigned int numberOfThreads = 4;
    std::string dirName = "";
    try{
        unsigned int numberOfArgs = validateLengthOfInput(argc);
 
        if (numberOfArgs == 3){
            numberOfThreads = validateNumberOfThreads(argv[2]);
        }
        dirName = argv[1];
        validatePath(dirName);

    } catch(std::invalid_argument const& e) {   
        errorMessage(argv[0], e);
    }
    catch(std::out_of_range const& e)
    {
        errorMessage(argv[0], e);
    }
    
    return std::pair<std::string, unsigned int>(dirName, numberOfThreads);
}
