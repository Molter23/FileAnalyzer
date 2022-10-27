#pragma once

#include <chrono>
#include<memory>

class Timer
{
public: 
    Timer();
    ~Timer();
    void stop();
   
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTimePoint;
};