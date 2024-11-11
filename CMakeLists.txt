cmake_minimum_required(VERSION 3.20)

project(CppLearning VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Define the source directory as a macro
add_definitions(-DSOURCE_DIR="${CMAKE_SOURCE_DIR}/Resources")

# Add the subdirectories
add_subdirectory(Library)

# Header files
set(HEADER_FILES
    utils/thread_guard.h
    Helper/DeviceHelper.h
    Helper/CommandHelper.h

    Command/CommandId.h
    Command/CommandUtil.h
    Command/AbstractCommand.h
    Command/AbstractCommandResult.h
    Command/CommandFactory.h
    Command/DrawCommand.h
    Command/DimensionCommand.h
    Command/CommandConsumer.h
    Command/CommandQueue.h

    Handler/FileHandler.h
    Handler/CommandHandler.h

    Feature/DrawFeature.h

    Device/AbstractDevice.h
    Device/RoboticDevice.h
)

# Source files
set(SOURCE_FILES
    main.cpp

    Command/CommandFactory.cpp
    Command/CommandQueue.cpp
    Command/CommandConsumer.cpp

    Handler/FileHandler.cpp
    Handler/CommandHandler.cpp

    Feature/DrawFeature.cpp

    Device/RoboticDevice.cpp
)

add_executable(draw-robot
    ${HEADER_FILES}
    ${SOURCE_FILES}
)

# Include directories if needed
target_include_directories(draw-robot PUBLIC
 ${CMAKE_SOURCE_DIR}/Device
 ${CMAKE_SOURCE_DIR}/Handler
 ${CMAKE_SOURCE_DIR}/Command
 ${CMAKE_SOURCE_DIR}/Feature
 ${CMAKE_SOURCE_DIR}/Helper
 ${CMAKE_SOURCE_DIR}/utils
 ${CMAKE_SOURCE_DIR}/Library/image-converter
 ${CMAKE_SOURCE_DIR}/Library/draw-algorithm
 )

# Link libraries if needed
target_link_libraries(draw-robot
    image-converter
    draw-algorithm
)