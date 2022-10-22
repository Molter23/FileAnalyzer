#pragma once

#include<iostream>
#include<experimental/filesystem>
#include<vector>
#include<atomic>

namespace fs = std::experimental::filesystem;

class Statistic
{
public:
    std::atomic<uint64_t> numberOfLines;
    uint64_t numberOfDiretories ;
    static Statistic& get();
    Statistic(const Statistic&) = delete;
private:
    Statistic();
};


std::ostream& operator<<(std::ostream& os, const Statistic& obj);

