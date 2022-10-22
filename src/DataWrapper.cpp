#include<iostream>
#include<experimental/filesystem>
#include<vector>
#include<atomic>

namespace fs = std::experimental::filesystem;

class DataWrapper
{
public:
    std::atomic<uint64_t> numberOfLines {0};
    uint64_t numberOfDiretories {0};

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



