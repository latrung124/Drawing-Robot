/*
* CommandConsumer.h
* Author: Trung La
* Description: This file contains the CommandConsumer class which is responsible for consuming commands.
*/

#ifndef COMMANDCONSUMER_H
#define COMMANDCONSUMER_H

#include <iostream>
#include <mutex>
#include "thread_guard.h"
#include <condition_variable>

#include "CommandQueue.h"

namespace dev::command {

using thread_guard = dev::utils::thread_guard;

class CommandConsumer {

public:
    CommandConsumer() = default;
    ~CommandConsumer();

    using AbstractCommandPtr = CommandQueue::AbstractCommandPtr;

    void start();
    void stop();

    void addCommand(AbstractCommandPtr command);

private:
    bool isConsumerAvailable() const;
    void loop();
    void consume(AbstractCommandPtr command);

    mutable std::mutex m_mutex;
    std::condition_variable m_conditionVariable;
    std::thread m_looper;
    CommandQueue m_commandQueue;
    bool m_isStop = false;
};

} // namespace dev::command

#endif // COMMANDCONSUMER_H