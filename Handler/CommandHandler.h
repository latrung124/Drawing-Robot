/*
* CommandHandler.h
* Author: Trung La
* Description: This file contains the CommandHandler class which is responsible for handling commands.
*/

#ifndef COMMANDHANDLER_H
#define COMMANDHANDLER_H

#include "AbstractHandler.h"
#include "AbstractCommand.h"

#include <queue>

namespace dev::handler {

class CommandHandler;

using CommandHandlerPtr = std::shared_ptr<CommandHandler>;

class CommandHandler : public AbstractHandler {
public:
    using AbstractHandler::AbstractHandler;
    using HandlerType = dev::handler::HandlerType;
    using AbstractCommand = dev::command::AbstractCommand;

    CommandHandler() = default;
    virtual ~CommandHandler() = default;

    HandlerType type() const override {
        return HandlerType::Command;
    }

    void addCommand(std::unique_ptr<AbstractCommand> command);
    void executeCommands();

private:
    std::queue<std::unique_ptr<AbstractCommand>> m_commandQueue;
};

} // namespace dev::handler

#endif // COMMANDHANDLER_H