/*
* AbstractCommand.h
* Author: Trung La
* Description: This file contains the AbstractCommand class which is responsible for handling commands.
*/

#ifndef ABSTRACTCOMMAND_H
#define ABSTRACTCOMMAND_H

#include "CommandId.h"
namespace dev::command {

class AbstractCommand {
public:
    AbstractCommand() = default;
    virtual ~AbstractCommand() = default;
    virtual CommandId id() const = 0;
};

} // namespace dev::command

#endif // ABSTRACTCOMMAND_H