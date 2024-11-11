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
    : m_commandConsumer(std::make_unique<CommandConsumer>())
{
}

CommandHandler::~CommandHandler()
{
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

void CommandHandler::send(const std::string_view& command) const
{
    std::istringstream stream(command.data());
    std::string commandName;
    stream >> commandName;
    std::cout << "Sending command: " << commandName << std::endl;
    auto commanId = dev::helper::getCommandId(commandName);
    auto commandPtr = dev::command::CommandFactory::getInstance().createCommand(commanId);
    if (commandPtr) {
        m_commandConsumer->addCommand(std::move(commandPtr));
    }
}

} // namespace dev::handler
