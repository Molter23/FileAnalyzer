#include<iostream>
#include<experimental/filesystem>
#include<vector>

namespace fs = std::experimental::filesystem;

#include "DataWrapper.hpp"

DataWrapper& DataWrapper::get()
{
    static DataWrapper _dwInstance;
    return _dwInstance;
}

DataWrapper::DataWrapper() {}




