cmake_minimum_required(VERSION 3.10)
project(FileAnalyzer)

set(CMAKE_CXX_STANDARD 17)

link_libraries(stdc++fs)

include_directories(src)

add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(lib/googletest)