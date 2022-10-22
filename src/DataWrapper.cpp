#include<iostream>
#include<experimental/filesystem>
#include<vector>

namespace fs = std::experimental::filesystem;

class DataWrapper
{
public:
    std::vector<fs::directory_entry> fillesInAllDirectories;

    static DataWrapper& get()
    {
        return _dwInstance;
    }

    DataWrapper(const DataWrapper&) = delete;

private:
    DataWrapper() {}
    static DataWrapper _dwInstance;
};



