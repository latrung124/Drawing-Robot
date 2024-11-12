/*
* CommandFactory.h
* Author: Trung La
* Description: This file contains the CommandFactory class which is responsible for creating commands.
*/

#ifndef COMMANDFACTORY_H
#define COMMANDFACTORY_H

#include <memory>

#include "AbstractCommand.h"

namespace dev::command {

class DimensionCommand;
class DrawLineCommand;
class MoveCommand;
class DrawCircleCommand;

class CommandFactory {
public:
    static CommandFactory& getInstance();

    virtual ~CommandFactory() = default;

    using AbstractCommandPtr = std::unique_ptr<AbstractCommand>;

    AbstractCommandPtr createCommand(CommandId id, const std::string& commandInfo);

private:
    CommandFactory() = default;

    std::unique_ptr<DimensionCommand> constructDimensionCommand(const std::string& commandInfo);
    std::unique_ptr<DrawLineCommand> constructDrawLineCommand(const std::string& commandInfo);
    std::unique_ptr<MoveCommand> constructMoveCommand(const std::string& commandInfo);
    std::unique_ptr<DrawCircleCommand> constructDrawCircleCommand(const std::string& commandInfo);
};

} // namespace dev::command

#endif // COMMANDFACTORY_H