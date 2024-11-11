/*
* CommandFactory.cpp
* Author: Trung La
* Description: This file contains the CommandFactory class which is responsible for creating commands.
*/

#include "CommandFactory.h"
#include "DrawCommand.h"
#include "DimensionCommand.h"

namespace dev::command {

using AbstractCommandPtr = CommandFactory::AbstractCommandPtr;

CommandFactory& CommandFactory::getInstance() {
    static CommandFactory instance;
    return instance;
}

AbstractCommandPtr CommandFactory::createCommand(CommandId id) {
    switch (id) {
        case CommandId::Dimension:
            return std::make_unique<DimensionCommand>();
        case CommandId::DrawLine:
            return std::make_unique<DrawLineCommand>();
        case CommandId::Move:
            return std::make_unique<MoveCommand>();
        case CommandId::DrawCircle:
            return std::make_unique<DrawCircleCommand>();
        default:
            return nullptr;
    }
}

} // namespace dev::command