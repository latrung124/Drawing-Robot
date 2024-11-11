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

class CommandFactory {
public:
    static CommandFactory& getInstance();

    virtual ~CommandFactory() = default;

    using AbstractCommandPtr = std::unique_ptr<AbstractCommand>;

    AbstractCommandPtr createCommand(CommandId id);

private:
    CommandFactory() = default;
};

} // namespace dev::command

#endif // COMMANDFACTORY_H