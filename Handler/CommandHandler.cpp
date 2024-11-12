/*
* CommandHandler.cpp
* Author: Trung La
* Description: This file contains the CommandHandler class which is responsible for handling commands.
*/

#include <sstream>

#include "CommandFactory.h"
#include "CommandHelper.h"
#include "CommandHandler.h"

namespace dev::handler {

CommandHandler::CommandHandler()
    : m_commandConsumer(std::make_unique<CommandConsumer>(this))
{
}

CommandHandler::~CommandHandler()
{
    stop();
}

void CommandHandler::start()
{
    std::cout << "CommandHandler started!" << std::endl;
    m_commandConsumer->start();
}

void CommandHandler::stop()
{
    std::cout << "CommandHandler stopped!" << std::endl;
    m_commandConsumer->stop();
}

void CommandHandler::send(const std::string_view& command, std::function<void(const AbstractCommandResult&)> callBackToDevice) const
{
    std::istringstream stream(command.data());
    std::string commandName;
    stream >> commandName;
    std::cout << "Sending command: " << commandName << std::endl;

    auto commanId = dev::helper::getCommandId(commandName);
    if(commanId == dev::command::CommandId::None) {
        std::cerr << "Invalid command: " << commandName << std::endl;
        return;
    }

    std::string commandInfo;
    try {
        commandInfo = command.substr(commandName.size());
    } catch (const std::out_of_range& e) {
        std::cerr << "Failed to extract command info: " << e.what() << std::endl;
        return;
    }

    auto commandPtr = dev::command::CommandFactory::getInstance().createCommand(commanId, commandInfo);
    if (!commandPtr) {
        std::cerr << "Failed to create command!" << std::endl;
        return;
    }
    auto callBack = [&, callBackToDevice](const dev::command::AbstractCommandResult& result) {
        callBackToDevice(result);
    };
    commandPtr->registerResultListener(callBack);

    m_commandConsumer->addCommand(std::move(commandPtr));
}

void CommandHandler::setDataStorage(const std::weak_ptr<dev::data::AbstractDataStorage>& dataStorage)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    m_dataStorage = dataStorage;
}

std::weak_ptr<dev::data::AbstractDataStorage> CommandHandler::dataStorage() const
{
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_dataStorage;
}

} // namespace dev::handler