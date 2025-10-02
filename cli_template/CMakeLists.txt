
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

# ---------- Project version ----------
set(PROJECT_VERSION_MAJOR 0)
set(PROJECT_VERSION_MINOR 1)
set(PROJECT_VERSION_REVISION 0)

# ---------- Determine compiler ----------
set(COMPILER_DIR ${CMAKE_CXX_COMPILER_ID})

# ---------- Determine architecture ----------
if(WIN32)
    string(TOLOWER "${CMAKE_SYSTEM_PROCESSOR}" SYS_PROC_LOWER)
    if(SYS_PROC_LOWER STREQUAL "amd64" OR SYS_PROC_LOWER STREQUAL "x86_64")
        set(ARCH_DIR "x64")
    elseif(SYS_PROC_LOWER STREQUAL "x86")
        set(ARCH_DIR "Win32")
    elseif(SYS_PROC_LOWER STREQUAL "arm64")
        set(ARCH_DIR "ARM64")
    else()
        set(ARCH_DIR "${CMAKE_SYSTEM_PROCESSOR}")
    endif()
else()
    # For Linux/macOS, use system processor as-is
    string(TOLOWER "${CMAKE_SYSTEM_PROCESSOR}" SYS_PROC_LOWER)
    if(SYS_PROC_LOWER STREQUAL "x86_64")
        set(ARCH_DIR "x64")
    elseif(SYS_PROC_LOWER STREQUAL "aarch64")
        set(ARCH_DIR "ARM64")
    else()
        set(ARCH_DIR "${CMAKE_SYSTEM_PROCESSOR}")
    endif()
endif()

# ---------- Define output directory ----------
set(OUTPUT_DIR ${CMAKE_SOURCE_DIR}/${COMPILER_DIR}-${ARCH_DIR}-$<CONFIG>-${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_REVISION})

# ---------- Apply to targets ----------
foreach(target tool1 tool2)  # add all your targets here
    set_target_properties(${target} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR}   # .exe / DLLs
        ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_DIR}   # .lib / static libs
        LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_DIR}   # shared libs / DLLs
    )
endforeach()
