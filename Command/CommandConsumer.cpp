/*
* CommandConsumer.cpp
* Author: Trung La
* Description: This file contains the implementation of the CommandConsumer class which is responsible for consuming commands.
*/

#include "CommandConsumer.h"
#include "DrawCommand.h"

namespace dev::command {

CommandConsumer::~CommandConsumer() {
}

void CommandConsumer::start() {
    m_isStop = false;
    //TODO: fix the thread loop issue
    // std::thread consumerThread(&CommandConsumer::loop, this);
    // thread_guard loopTask(consumerThread);
}

void CommandConsumer::stop() {
    std::cout << "Stopping CommandConsumer" << std::endl;
    std::lock_guard<std::mutex> lock(m_mutex);
    m_isStop = true;

    m_conditionVariable.notify_one(); //ensure the thread is not blocked
}

bool CommandConsumer::isConsumerAvailable() const {
    return m_isStop || m_commandQueue.isAvailable();
}

void CommandConsumer::addCommand(AbstractCommandPtr command) {
    std::cout << "Adding command " << static_cast<uint16_t>(command->id()) << std::endl;
    std::lock_guard<std::mutex> lock(m_mutex);
    m_commandQueue.push(std::move(command));

    m_conditionVariable.notify_one();
}

void CommandConsumer::loop() {
    std::cout << "CommandConsumer loop started!, threadid: " << std::this_thread::get_id() << std::endl;
    while(true) {
        std::unique_lock<std::mutex> lock(m_mutex);
        std::cerr << "CommandConsumer is waiting... \n";
        m_conditionVariable.wait(lock, [this] {
            return isConsumerAvailable();
        });

        if (m_isStop && !m_commandQueue.isAvailable()) {
            std::cerr << "CommandConsumer is stopping! \n";
            break;
        }

        std::cerr << "CommandConsumer finishes waiting! \n";

        if (m_commandQueue.isAvailable()) {
            auto command = m_commandQueue.pop();
            lock.unlock();

            consume(std::move(command));
        }
    }
}

void CommandConsumer::consume(AbstractCommandPtr command) {
    // Consume command
    std::cout << "Consuming command " << static_cast<uint16_t>(command->id()) << std::endl;

    switch (command->id())
    {
    case CommandId::Draw: {
        auto drawCommand = dynamic_cast<DrawCommand*>(command.get());
        if (drawCommand) {
            drawCommand->draw();
        }
        break;
    }
    case CommandId::Move: {
        auto moveCommand = dynamic_cast<MoveCommand*>(command.get());
        if (moveCommand) {
            moveCommand->move();
        }
        break;
    }
    default:
        std::cout << "Command not supported!" << std::endl;
        break;
    }
}

} // namespace dev::command