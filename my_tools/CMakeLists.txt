cmake_minimum_required(VERSION 3.16)
project(my_tools LANGUAGES CXX)

# Set C++ standard globally
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add subdirectories for each tool
add_subdirectory(common)
add_subdirectory(tool1)
add_subdirectory(tool2)
