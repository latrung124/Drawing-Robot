/*
* CommandConsumer.cpp
* Author: Trung La
* Description: This file contains the implementation of the CommandConsumer class which is responsible for consuming commands.
*/

#include "CommandConsumer.h"
#include "DrawCommand.h"
#include "DimensionCommand.h"

namespace dev::command {

CommandConsumer::~CommandConsumer() {
    thread_guard guard(m_looper);
}

void CommandConsumer::start() {
    m_isStop = false;
    m_looper =  std::thread(&CommandConsumer::loop, this);
}

void CommandConsumer::stop() {
    std::cout << "Stopping CommandConsumer" << std::endl;
    m_isStop = true;
    m_conditionVariable.notify_all(); //ensure the thread is not blocked
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
    case CommandId::Dimension: {
        auto dimensionCommand = dynamic_cast<DimensionCommand*>(command.get());
        if (dimensionCommand) {
            // Create a new dimension
        }
        break;
    }
    case CommandId::DrawLine: {
        auto drawCommand = dynamic_cast<DrawLineCommand*>(command.get());
        if (drawCommand) {
            drawCommand->draw();
            //Use internal algorithm library to get bytes array of bmp image
        }
        break;
    }
    case CommandId::Move: {
        auto moveCommand = dynamic_cast<MoveCommand*>(command.get());
        if (moveCommand) {
            moveCommand->move();
            //Use internal algorithm library to get bytes array of bmp image
        }
        break;
    }
    default:
        std::cout << "Command not supported!" << std::endl;
        break;
    }
}

} // namespace dev::command