#include<iostream>
#include<experimental/filesystem>
#include<fstream>
#include<stdexcept>
#include<vector>

namespace fs = std::experimental::filesystem;

void usage(const std::string& programName)
{
    std::cout <<"Usage: " << std::endl << std::endl;
    std::cout << "\t" << programName << " [path to directory]" << std::endl << std::endl;
}

void validateInput(int argc, char** argv)
{
    try{
        if(argc > 2)
            throw std::invalid_argument("Too many arguments spcified.");
        
        if(argc == 1)
            throw std::invalid_argument("Path not spcified.");

        std::string dirName = argv[1];

        if(!fs::is_directory(fs::status(dirName)))
            throw std::invalid_argument("Given argument is not a path to directory.");
    } 
    catch(std::invalid_argument const& e)
    {   
        std::cerr << e.what() << std::endl;
        std::string programName = argv[0];
        usage(programName);
    }       
}




int main(int argc, char** argv)
{   
    validateInput(argc, argv);



    /*for (auto const& dir_entry : fs::recursive_directory_iterator("/"))
    {
        std::cout << dir_entry << '\n';
    }*/

}