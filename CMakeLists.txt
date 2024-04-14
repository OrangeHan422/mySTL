cmake_minimum_required(VERSION 3.10.2)
project(mySTL LANGUAGES CXX)

add_executable(mySTL
            main.cpp)  


target_include_directories(mySTL 
PUBLIC
${PROJECT_SOURCE_DIR}/include)

