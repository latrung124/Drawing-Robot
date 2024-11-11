/*
* CommandHandler.h
* Author: Trung La
* Description: This file contains the CommandHandler class which is responsible for handling commands.
*/

#ifndef COMMANDHANDLER_H
#define COMMANDHANDLER_H

#include <string_view>

#include "AbstractHandler.h"
#include "AbstractCommand.h"
#include "CommandConsumer.h"

namespace dev::handler {

class CommandHandler;

using CommandHandlerPtr = std::shared_ptr<CommandHandler>;

class CommandHandler : public AbstractHandler {
public:
    using AbstractHandler::AbstractHandler;
    using HandlerType = dev::handler::HandlerType;
    using AbstractCommand = dev::command::AbstractCommand;
    using CommandConsumer = dev::command::CommandConsumer;

    CommandHandler();
    virtual ~CommandHandler();

    void start() override;
    void stop() override;

    HandlerType type() const override {
        return HandlerType::Command;
    }

    void send(const std::string_view& command) const;

private:
    std::unique_ptr<CommandConsumer> m_commandConsumer;
};

} // namespace dev::handler

#endif // COMMANDHANDLER_H