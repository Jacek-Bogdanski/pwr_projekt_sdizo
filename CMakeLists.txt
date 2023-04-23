cmake_minimum_required(VERSION 3.24)
project(pwr_projekt_sdizo)

#Set Linker flags
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")

set(CMAKE_CXX_STANDARD 11)


add_executable(sdizo main.cpp source/MyArray.cpp source/MyList.cpp source/MyHeap.cpp source/MyBST.cpp)
