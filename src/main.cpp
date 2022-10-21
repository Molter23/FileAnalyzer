#include<iostream>
#include<experimental/filesystem>
#include<fstream>

namespace fs = std::experimental::filesystem;

int main(int argc, char** argv)
{
    
    for (auto const& dir_entry : fs::recursive_directory_iterator("/"))
    {
        std::cout << dir_entry << '\n';
    }

}