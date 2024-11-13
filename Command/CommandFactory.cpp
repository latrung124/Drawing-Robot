/*
 * CommandFactory.cpp
 * Author: Trung La
 * Description: This file contains the CommandFactory class which is responsible for creating commands.
 */

#include "CommandFactory.h"
#include "DimensionCommand.h"
#include "DrawCommand.h"
#include <iostream>
#include <sstream>

namespace dev::command {

CommandFactory &CommandFactory::getInstance()
{
	static CommandFactory instance;
	return instance;
}

AbstractCommandPtr CommandFactory::createCommand(CommandId id, const std::string &commandInfo)
{
	switch (id) {
	case CommandId::Dimension:
		return constructDimensionCommand(commandInfo);
	case CommandId::DrawLine:
		return constructDrawLineCommand(commandInfo);
	case CommandId::Move:
		return constructMoveCommand(commandInfo);
	case CommandId::DrawCircle:
		return constructDrawCircleCommand(commandInfo);
	default:
		return nullptr;
	}
}

std::unique_ptr<DimensionCommand> CommandFactory::constructDimensionCommand(
    const std::string &commandInfo)
{
	// apply for square grid dimension
	uint16_t height = 0;

	std::istringstream stream(commandInfo);
	while (stream.good()) {
		if (!(stream >> height)) {
			throw std::invalid_argument("Invalid commandInfo format: " + commandInfo);
		}
	}

	if (height <= 0) {
		throw std::invalid_argument("commandInfo must contain a valid height: " + commandInfo);
	} else if (height > UINT16_MAX) {
		height = UINT16_MAX;
	}

	return std::make_unique<DimensionCommand>(Dimension{height, height});
}

std::unique_ptr<DrawLineCommand> CommandFactory::constructDrawLineCommand(
    const std::string &commandInfo)
{
	std::vector<Point> points;

	std::istringstream stream(commandInfo);
	while (stream.good()) {
		Point point;
		char comma;
		if (!(stream >> point.x >> comma >> point.y)) {
			throw std::invalid_argument("Invalid commandInfo format: " + commandInfo);
		}

		if (point.x < 0 || point.y < 0 || point.x > UINT16_MAX || point.y > UINT16_MAX) {
			throw std::invalid_argument("commandInfo must contain valid points: " + commandInfo);
		}

		points.push_back(point);
	}

	if (points.empty()) {
		throw std::invalid_argument("commandInfo must contain at least one point: " + commandInfo);
	}

	return std::make_unique<DrawLineCommand>(Line{points});
}

std::unique_ptr<MoveCommand> CommandFactory::constructMoveCommand(const std::string &commandInfo)
{
	Point point;

	std::istringstream stream(commandInfo);
	while (stream.good()) {
		char comma;
		if (!(stream >> point.x >> comma >> point.y)) {
			throw std::invalid_argument("Invalid commandInfo format: " + commandInfo);
		}
	}

	if (point.x < 0 || point.y < 0 || point.x > UINT16_MAX || point.y > UINT16_MAX) {
		throw std::invalid_argument("commandInfo must contain valid point: " + commandInfo);
	}

	return std::make_unique<MoveCommand>(point);
}

std::unique_ptr<DrawCircleCommand> CommandFactory::constructDrawCircleCommand(
    const std::string &commandInfo)
{
	return std::make_unique<DrawCircleCommand>();
}

} // namespace dev::command
