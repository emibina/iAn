cmake_minimum_required(VERSION 3.10)
project(my_cli_tools VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)

# Add CLI Parser library
add_library(cli_parser src/cli_parser.cpp)
target_include_directories(cli_parser PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc)

# Add each tool as a separate executable
add_executable(tool1 src/main.cpp)
target_link_libraries(tool1 PRIVATE cli_parser)

# You can add more tools here
# add_executable(tool2 src/tool2.cpp)
# target_link_libraries(tool2 PRIVATE cli_parser)

# Put all executables into bin/
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
