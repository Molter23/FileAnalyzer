set(BINARY ${CMAKE_PROJECT_NAME})

set(SOURCES ${SOURCES})

add_executable(${BINARY}_run  main.cpp InputValidation.cpp DataWrapper.cpp Statistic.cpp Analyzer.cpp Timer.cpp)
add_library(${BINARY}_lib STATIC  main.cpp InputValidation.cpp DataWrapper.cpp Statistic.cpp  Analyzer.cpp Timer.cpp)