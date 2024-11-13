/*
 * CommandHelper.h
 * Author: Trung La
 * Description: This file contains the CommandHelper class which is responsible for handling commands.
 */

#ifndef COMMANDHELPER_H
#define COMMANDHELPER_H

#include "CommandId.h"
#include "CommandUtil.h"

namespace dev::helper {

using CommandId = dev::command::CommandId;

CommandId getCommandId(const std::string_view &command)
{
	// find command in map with string view
	using namespace dev::command;

	auto it = gCommandIdMap.find(command);
	if (it != gCommandIdMap.end()) {
		return it->second;
	}

	return CommandId::None;
}

} // namespace dev::helper

#endif // COMMANDHELPER_H
