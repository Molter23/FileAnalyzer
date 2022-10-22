#include<iostream>
#include<experimental/filesystem>
#include<vector>
#include<atomic>

namespace fs = std::experimental::filesystem;

class Statistic
{
public:
    std::atomic<uint64_t> numberOfLines{0};
    uint64_t numberOfDiretories {0};

    static Statistic& get()
    {
        return _sInstance;
    }

    Statistic(const Statistic&) = delete;

private:
    Statistic() {}
    static Statistic _sInstance;
};



