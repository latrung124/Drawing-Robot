/*
* CommandFactory.cpp
* Author: Trung La
* Description: This file contains the CommandFactory class which is responsible for creating commands.
*/


#include <iostream>
#include <sstream>
#include "CommandFactory.h"
#include "DrawCommand.h"
#include "DimensionCommand.h"

namespace dev::command {

using AbstractCommandPtr = CommandFactory::AbstractCommandPtr;

CommandFactory& CommandFactory::getInstance() {
    static CommandFactory instance;
    return instance;
}

AbstractCommandPtr CommandFactory::createCommand(CommandId id, const std::string& commandInfo) {
    switch (id) {
        case CommandId::Dimension:
            return constructDimensionCommand(commandInfo);
        case CommandId::DrawLine:
            return constructDrawLineCommand(commandInfo);
        case CommandId::Move:
            return constructMoveCommand(commandInfo);
        case CommandId::DrawCircle:
            return constructDrawCircleCommand(commandInfo);
        default:
            return nullptr;
    }
}

std::unique_ptr<DimensionCommand> CommandFactory::constructDimensionCommand(const std::string& commandInfo) {
    std::istringstream stream(commandInfo);
    //apply for square grid dimension
    int height;
    stream >> height;
    if (height <= 0) {
        std::cerr << "Invalid height" << std::endl;
        return nullptr;
    }

    return std::make_unique<DimensionCommand>(Dimension{height, height});
}

std::unique_ptr<DrawLineCommand> CommandFactory::constructDrawLineCommand(const std::string& commandInfo) {
    std::istringstream stream(commandInfo);
    std::vector<Point> points;
    Point endPoint;
    char comma;
    stream >> endPoint.x >> comma >> endPoint.y;
    points.push_back(endPoint);

    return std::make_unique<DrawLineCommand>(Line{points});
}

std::unique_ptr<MoveCommand> CommandFactory::constructMoveCommand(const std::string& commandInfo) {
    std::istringstream stream(commandInfo);
    Point point;
    char comma;
    stream >> point.x >> comma >> point.y;

    return std::make_unique<MoveCommand>(point);
}

std::unique_ptr<DrawCircleCommand> CommandFactory::constructDrawCircleCommand(const std::string& commandInfo) {
    return std::make_unique<DrawCircleCommand>();
}

} // namespace dev::command