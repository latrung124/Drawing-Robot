/*
* AbstractCommand.h
* Author: Trung La
* Description: This file contains the AbstractCommand class which is responsible for handling commands.
*/

#ifndef ABSTRACTCOMMAND_H
#define ABSTRACTCOMMAND_H

namespace dev::command {

enum class CommandId : uint16_t {
    None,
    Draw,
    Move,
};

class AbstractCommand {
public:
    AbstractCommand() = default;
    virtual ~AbstractCommand() = default;
    virtual CommandId id() const = 0;
};

} // namespace dev::command

#endif // ABSTRACTCOMMAND_H