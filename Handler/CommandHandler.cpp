/*
* CommandHandler.cpp
* Author: Trung La
* Description: This file contains the CommandHandler class which is responsible for handling commands.
*/

#include <iostream>

#include "CommandHandler.h"

namespace dev::handler {

void CommandHandler::addCommand(std::unique_ptr<AbstractCommand> command)
{
    // TODO: implement condition variable for queue because
    // it should be thread safe when doing the file handling
    std::cout << "Adding command to queue" << std::endl;
    m_commandQueue.push(std::move(command));
}

void CommandHandler::executeCommands()
{
    // TODO: implement condition variable for queue because
    // it should be thread safe when doing the file handling
    std::cout << "Executing commands" << std::endl;
    while (!m_commandQueue.empty()) {
        m_commandQueue.pop();
        std::cout << "Command executed" << std::endl;
    }
}

} // namespace dev::handler
