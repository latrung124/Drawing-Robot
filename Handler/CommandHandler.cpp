/*
* CommandHandler.cpp
* Author: Trung La
* Description: This file contains the CommandHandler class which is responsible for handling commands.
*/

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

void CommandHandler::send(const std::string& command) const
{
    std::cout << "Sending command: " << command << std::endl;
}

void CommandHandler::send(std::unique_ptr<AbstractCommand> command)
{
    m_commandConsumer->addCommand(std::move(command));
}

} // namespace dev::handler
