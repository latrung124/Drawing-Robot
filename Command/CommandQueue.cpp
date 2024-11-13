/*
 * CommandQueue.cpp
 * Author: Trung La
 * Description: This file contains the implementation of the CommandQueue class which is responsible
 * for queuing commands.
 */

#include "CommandQueue.h"
#include "AbstractDataStorage.h"

namespace dev::command {

bool CommandQueue::isAvailable() const
{
	return !m_commandQueue.empty();
}

void CommandQueue::push(AbstractCommandPtr command)
{
	m_commandQueue.push(std::move(command));
}

AbstractCommandPtr CommandQueue::pop()
{
	if (m_commandQueue.empty()) {
		return nullptr;
	}
	AbstractCommandPtr command = std::move(m_commandQueue.front());
	m_commandQueue.pop();

	return command;
}

} // namespace dev::command
