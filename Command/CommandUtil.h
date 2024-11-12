/*
* CommandUtil.h
* Author: Trung La
* Description: This file contains the CommandUtil class which is responsible for handling commands.
*/

#ifndef COMMANDUTIL_H
#define COMMANDUTIL_H

#include <string_view>
#include <unordered_map>

#include "CommandId.h"

namespace dev::command {

inline const std::unordered_map<std::string_view, CommandId> gCommandIdMap = {
    {"None", CommandId::None},
    {"DIMENSION", CommandId::Dimension},
    {"LINE_TO", CommandId::DrawLine},
    {"CIRCLE", CommandId::DrawCircle},
    {"MOVE_TO", CommandId::Move},
};

} // namespace dev::command

#endif // COMMANDUTIL_H