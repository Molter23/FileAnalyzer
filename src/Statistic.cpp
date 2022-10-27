#include<iostream>
#include<experimental/filesystem>
#include<vector>
#include<atomic>

#include "Statistic.hpp"

namespace fs = std::experimental::filesystem;

Statistic& Statistic::get()
{
    static Statistic _sInstance;
    return _sInstance; 
}

Statistic::Statistic() {};

std::ostream& operator<<(std::ostream& os, const Statistic& obj)
{
    return os << "Number of directories: " << obj.numberOfDiretories << std::endl << "Number of lines: " 
                << obj.numberOfLines << std::endl << "Number of not empty lines: " <<  obj.numberOfLines - obj.numberOfEmptyLines << std::endl;
}

