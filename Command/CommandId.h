/*
* CommandId.h
* Author: Trung La
* Description: This file contains the CommandId enum class which is responsible for handling command ids.
*/

#ifndef COMMANDID_H
#define COMMANDID_H

namespace dev::command {

enum class CommandId : uint16_t {
    None,
    Draw,
    Move,
};

} // namespace dev::command

#endif // COMMANDID_H