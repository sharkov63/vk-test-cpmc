cmake_minimum_required(VERSION 3.5)

# Project name
project(cpmc)

# Sources
set(CMAKE_SOURCE_DIR "src/")
file(GLOB_RECURSE SOURCES "${CMAKE_SOURCE_DIR}/*.cpp")

# Compilation
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")

# Executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Include directories
target_include_directories(${PROJECT_NAME}
    PRIVATE
        "include/"
)


