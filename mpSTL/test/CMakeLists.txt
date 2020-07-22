cmake_minimum_required(VERSION 3.16.3)
project(stlTest)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")
 
#Bring the headers, such as Student.h into the project
include_directories(../include)
 
#Can manually add the sources using the set command as follows:
# set(SOURCES test.cpp) 
 
#However, the file(GLOB...) allows for wildcard additions:
file(GLOB SOURCES "../src/*.cpp" "test.cpp")
 
add_executable(main ${SOURCES})