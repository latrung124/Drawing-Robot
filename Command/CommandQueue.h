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

namespace dev::command {

class CommandQueue {
public:
    CommandQueue() = default;
    ~CommandQueue() = default;

    using AbstractCommandPtr = std::unique_ptr<AbstractCommand>;

    void push(AbstractCommandPtr command);
    AbstractCommandPtr pop();

    bool isAvailable() const;

private:
    std::queue<AbstractCommandPtr> m_commandQueue;
};

} // namespace dev::command

#endif // COMMANDQUEUE_H