cmake_minimum_required(VERSION 3.16)

# Project name and language
project(MyProject LANGUAGES CXX)

# Use C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Allow including headers from "include/"
include_directories(${PROJECT_SOURCE_DIR}/inc)

# Source files
set(SOURCES
    src/main.cpp
    src/hello.cpp
)

# Define executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Example: if later you want to use Qt
# find_package(Qt6 COMPONENTS Core Widgets REQUIRED)
# target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Core Qt6::Widgets)

# Organize projects in IDEs like Visual Studio
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})
