/*
 * CommandConsumer.cpp
 * Author: Trung La
 * Description: This file contains the implementation of the CommandConsumer class which is
 * responsible for consuming commands.
 */

#include "CommandConsumer.h"
#include "AbstractCommandResult.h"
#include "CommandHandler.h"
#include "DimensionCommand.h"
#include "DrawCommand.h"
#include "RoboticDataStorage.h"

#include "draw_algorithm.h"

namespace dev::command {

CommandConsumer::CommandConsumer(const dev::handler::CommandHandler *commandHandler)
    : m_commandHandler(commandHandler)
{
}

CommandConsumer::~CommandConsumer()
{
	thread_guard guard(m_looper);
}

void CommandConsumer::start()
{
	m_isStop = false;
	m_looper = std::thread(&CommandConsumer::loop, this);
}

void CommandConsumer::stop()
{
	std::cout << "Stopping CommandConsumer" << std::endl;
	m_isStop = true;
	m_conditionVariable.notify_all(); // ensure the thread is not blocked
}

bool CommandConsumer::canProcessCommands() const
{
	return m_isStop || m_commandQueue.isAvailable();
}

void CommandConsumer::addCommand(AbstractCommandPtr command)
{
	std::cout << "Adding command " << static_cast<uint16_t>(command->id()) << std::endl;
	std::lock_guard<std::mutex> lock(m_mutex);
	m_commandQueue.push(std::move(command));

	m_conditionVariable.notify_one();
}

void CommandConsumer::loop()
{
	std::cout
	    << "CommandConsumer loop started!, threadid: " << std::this_thread::get_id() << std::endl;
	while (true) {
		std::unique_lock<std::mutex> lock(m_mutex);
		std::cerr << "CommandConsumer is waiting... \n";
		m_conditionVariable.wait(lock, [this] { return canProcessCommands(); });

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

bool CommandConsumer::consumeDimensionCommand(AbstractCommand *command)
{
	auto dimensionCommand = dynamic_cast<DimensionCommand *>(command);
	if (!dimensionCommand) {
		return false;
	}

	try {
		if (!m_commandHandler->dataStorage().lock()) {
			std::cerr << "Data storage is not available!" << std::endl;
			return false;
		}
		if (m_commandHandler->dataStorage().lock()->type()
		    != dev::data::DataStorageType::RoboticDataStorage) {
			std::cerr << "Data storage is not RoboticDataStorage!" << std::endl;
			return false;
		}

		auto dataStorage = std::dynamic_pointer_cast<dev::data::RoboticDataStorage>(
		    m_commandHandler->dataStorage().lock());
		dev::data::RoboticData data;
		data.map2D.width = dimensionCommand->getDimension().width;
		data.map2D.height = dimensionCommand->getDimension().height;
		data.map2D.data.resize(data.map2D.width, std::vector<uint16_t>(data.map2D.height, 0));
		dataStorage->storeData(data);

		std::cout << "New dimension: " << data.map2D.width << "x" << data.map2D.height << std::endl;
		return true;
	} catch (const std::exception &e) {
		std::cerr << "Failed to consume DimensionCommand: " << e.what() << std::endl;
		return false;
	}
}

bool CommandConsumer::consumeDrawLineCommand(AbstractCommand *command)
{
	auto drawCommand = dynamic_cast<DrawLineCommand *>(command);
	if (!drawCommand) {
		return false;
	}
	try {
		auto dataStorage = std::dynamic_pointer_cast<dev::data::RoboticDataStorage>(
		    m_commandHandler->dataStorage().lock());
		if (!dataStorage) {
			std::cerr << "Data storage is not available!" << std::endl;
			return false;
		}

		auto roboticData = dataStorage->getData();
		auto target = drawCommand->getLine().points.back();
		if (target.x >= roboticData.map2D.width || target.y >= roboticData.map2D.height) {
			std::cerr << "Invalid draw line command!" << std::endl;
			return false;
		}

		draw_algorithm::draw_data drawData;
		drawData.type = draw_algorithm::utils::draw_type::LINE;
		drawData.start.x = roboticData.pos.x;
		drawData.start.y = roboticData.pos.y;
		drawData.end.x = target.x;
		drawData.end.y = target.y;
		drawData.grid.width = roboticData.map2D.width;
		drawData.grid.height = roboticData.map2D.height;
		drawData.grid.data.assign(roboticData.map2D.data.begin(), roboticData.map2D.data.end());

		draw_algorithm::draw_algorithm drawAlgorithm;
		auto positions = drawAlgorithm.drawLine(drawData);

		for (auto &pos : positions) {
			roboticData.map2D.data[pos.x][pos.y] = 1;
		}

		dataStorage->storeData(roboticData);
		return true;

	} catch (const std::exception &e) {
		std::cerr << "Failed to consume DrawLineCommand: " << e.what() << std::endl;
		return false;
	}
}

bool CommandConsumer::consumeMoveCommand(AbstractCommand *command)
{
	auto moveCommand = dynamic_cast<MoveCommand *>(command);
	if (!moveCommand) {
		return false;
	}

	try {
		auto dataStorage = std::dynamic_pointer_cast<dev::data::RoboticDataStorage>(
		    m_commandHandler->dataStorage().lock());
		if (!dataStorage) {
			std::cerr << "Data storage is not available!" << std::endl;
			return false;
		}

		auto roboticData = dataStorage->getData();
		if (moveCommand->getPoint().x >= roboticData.map2D.width
		    || moveCommand->getPoint().y >= roboticData.map2D.height) {
			std::cerr << "Invalid move command!" << std::endl;
			return false;
		}
		roboticData.pos.x = moveCommand->getPoint().x;
		roboticData.pos.y = moveCommand->getPoint().y;

		dataStorage->storeData(roboticData);
		return true;
	} catch (const std::exception &e) {
		std::cerr << "Failed to consume MoveCommand: " << e.what() << std::endl;
		return false;
	}
}

void CommandConsumer::consume(AbstractCommandPtr command)
{
	// Consume command
	std::cout << "Consuming command " << static_cast<uint16_t>(command->id()) << std::endl;

	switch (command->id()) {
	case CommandId::Dimension: {
		dev::command::CommandResult result = dev::command::CommandResult::Success;
		if (!consumeDimensionCommand(command.get())) {
			std::cerr << "Failed to consume DimensionCommand!" << std::endl;
			result = dev::command::CommandResult::Failure;
		}
		AbstractCommandResult dimensionResult(dev::command::CommandId::Dimension, result);
		command->notifyCommandCompleted(dimensionResult);
		break;
	}
	case CommandId::DrawLine: {
		dev::command::CommandResult result = dev::command::CommandResult::Success;
		if (!consumeDrawLineCommand(command.get())) {
			std::cerr << "Failed to consume DrawLineCommand!" << std::endl;
			result = dev::command::CommandResult::Failure;
		}
		AbstractCommandResult drawLineResult(dev::command::CommandId::DrawLine, result);
		command->notifyCommandCompleted(drawLineResult);
		break;
	}
	case CommandId::Move: {
		dev::command::CommandResult result = dev::command::CommandResult::Success;
		if (!consumeMoveCommand(command.get())) {
			std::cerr << "Failed to consume MoveCommand!" << std::endl;
			result = dev::command::CommandResult::Failure;
		}
		AbstractCommandResult moveResult(dev::command::CommandId::Move, result);
		command->notifyCommandCompleted(moveResult);
		break;
	}
	default: {
		dev::command::CommandResult result = dev::command::CommandResult::Failure;
		AbstractCommandResult unknownResult(dev::command::CommandId::None, result);
		command->notifyCommandCompleted(unknownResult);
		std::cout << "Command not supported!" << std::endl;
		break;
	}
	}
}

} // namespace dev::command
