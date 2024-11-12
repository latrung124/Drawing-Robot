/*
* CommandHandler.h
* Author: Trung La
* Description: This file contains the CommandHandler class which is responsible for handling commands.
*/

#ifndef COMMANDHANDLER_H
#define COMMANDHANDLER_H

#include <string_view>
#include <functional>
#include <mutex>

#include "AbstractHandler.h"
#include "AbstractCommand.h"
#include "CommandConsumer.h"
#include "AbstractDataStorage.h"

namespace dev::handler {

class CommandHandler;

using CommandHandlerPtr = std::shared_ptr<CommandHandler>;

class CommandHandler : public AbstractHandler {
public:
    using AbstractHandler::AbstractHandler;
    using HandlerType = dev::handler::HandlerType;
    using AbstractCommand = dev::command::AbstractCommand;
    using AbstractCommandResult = dev::command::AbstractCommandResult;
    using CommandConsumer = dev::command::CommandConsumer;
    using AbstractDataStorage = dev::data::AbstractDataStorage;

    CommandHandler();
    virtual ~CommandHandler();

    void start() override;
    void stop() override;

    HandlerType type() const override {
        return HandlerType::Command;
    }

    void send(const std::string_view& command,
            std::function<void(const AbstractCommandResult&)> callBackToDevice) const;
    void setDataStorage(const std::weak_ptr<AbstractDataStorage>& dataStorage);
    std::weak_ptr<AbstractDataStorage> dataStorage() const;

private:
    mutable std::mutex m_mutex;
    std::unique_ptr<CommandConsumer> m_commandConsumer;
    std::weak_ptr<AbstractDataStorage> m_dataStorage;
};

} // namespace dev::handler

#endif // COMMANDHANDLER_H