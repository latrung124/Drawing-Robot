cmake_minimum_required(VERSION 3.20)

project(CppLearning VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Define the source directory as a macro
add_definitions(-DSOURCE_DIR="${CMAKE_SOURCE_DIR}/Resources")

# Header files
set(HEADER_FILES
    Helper/DeviceHelper.h

    Command/AbstractCommand.h
    Command/DrawCommand.h

    Handler/FileHandler.h
    Handler/CommandHandler.h

    Feature/DrawFeature.h

    Device/AbstractDevice.h
    Device/RoboticDevice.h
)

# Source files
set(SOURCE_FILES
    main.cpp

    Handler/FileHandler.cpp
    Handler/CommandHandler.cpp

    Feature/DrawFeature.cpp

    Device/RoboticDevice.cpp
)

add_executable(interview-home-test 
    ${HEADER_FILES}
    ${SOURCE_FILES}
)

# Include directories if needed
target_include_directories(interview-home-test PUBLIC
 ${CMAKE_SOURCE_DIR}/Device
 ${CMAKE_SOURCE_DIR}/Handler
 ${CMAKE_SOURCE_DIR}/Command
 ${CMAKE_SOURCE_DIR}/Feature
 ${CMAKE_SOURCE_DIR}/Helper
 )

# Link libraries if needed