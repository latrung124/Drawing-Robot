/*
 * CommandQueue.h
 * Author: Trung La
 * Description: This file contains the CommandQueue class which is responsible for queuing commands.
 */

#ifndef COMMANDQUEUE_H
#define COMMANDQUEUE_H

#include <memory>
#include <queue>

#include "AbstractCommand.h"

namespace dev {

namespace data {
class AbstractDataStorage;
}

namespace command {

class CommandQueue
{
public:
	CommandQueue() = default;
	~CommandQueue() = default;

	void push(AbstractCommandPtr command);
	AbstractCommandPtr pop();

	bool isAvailable() const;

private:
	std::queue<AbstractCommandPtr> m_commandQueue;
};

} // namespace command

} // namespace dev

#endif // COMMANDQUEUE_H
