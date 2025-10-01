
cmake_minimum_required(VERSION 3.20)
project(CLITools)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Common library
add_library(cli_common
    common/cli_base.cpp
)

target_include_directories(cli_common PUBLIC common)

# Tool 1
add_executable(tool1 tool1/main.cpp)
target_link_libraries(tool1 cli_common)

# Tool 2  
add_executable(tool2 tool2/main.cpp)
target_link_libraries(tool2 cli_common)

# On Windows, you might want to copy the executables to a common directory
if(WIN32)
    set_target_properties(tool1 tool2 PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    )
endif()
