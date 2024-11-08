cmake_minimum_required(VERSION 3.20)

project(CppLearning VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Define the source directory as a macro
add_definitions(-DSOURCE_DIR="${CMAKE_SOURCE_DIR}/Resources")

# Header files
set(HEADER_FILES
    Handler/FileHandler.h
)

# Source files
set(SOURCE_FILES
    main.cpp
    Handler/FileHandler.cpp
)

add_executable(interview-home-test 
    ${HEADER_FILES}
    ${SOURCE_FILES}
)

# Include directories if needed
# Link libraries if needed