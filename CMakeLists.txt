cmake_minimum_required(VERSION 3.24)
project(pwr_projekt_sdizo)

set(CMAKE_CXX_STANDARD 17)

# copy input file to
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/input.txt
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_executable(sdizo main.cpp source/MyArray.cpp source/MyList.cpp)
