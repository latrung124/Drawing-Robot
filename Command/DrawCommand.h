/*
 * DrawCommand.h
 * Author: Trung La
 * Description: This file contains the DrawCommand class which is responsible for handling commands.
 */

#ifndef DRAWCOMMAND_H
#define DRAWCOMMAND_H

#include <iostream>
#include <vector>

#include "AbstractCommand.h"
#include "AbstractCommandResult.h"

namespace dev::command {

struct Point
{
	uint16_t x;
	uint16_t y;
};

struct Line
{
	std::vector<Point> points;
};

class DrawCommand : public AbstractCommand
{
public:
	DrawCommand() = default;
	~DrawCommand() = default;

	virtual CommandId id() const = 0;

	virtual void draw() = 0;
};

class DrawLineCommand : public DrawCommand
{
public:
	DrawLineCommand()
	    : m_line({}){};

	DrawLineCommand(const Line &line)
	{
		m_line.points.assign(line.points.begin(), line.points.end());
	};

	~DrawLineCommand() = default;

	CommandId id() const override
	{
		return CommandId::DrawLine;
	}

	void setLine(const Line &line)
	{
		m_line.points.assign(line.points.begin(), line.points.end());
	}

	Line getLine() const
	{
		return m_line;
	}

	void draw()
	{
		std::cout << "Drawing line" << std::endl;
	}

private:
	Line m_line;
};

class DrawCircleCommand : public DrawCommand
{
public:
	DrawCircleCommand() = default;
	~DrawCircleCommand() = default;

	CommandId id() const override
	{
		return CommandId::DrawCircle;
	}

	void draw()
	{
		std::cout << "Drawing circle" << std::endl;
	}
};

class MoveCommand : public AbstractCommand
{
public:
	MoveCommand() = default;

	MoveCommand(const Point &point)
	    : point(point)
	{
	}

	~MoveCommand() = default;

	CommandId id() const override
	{
		return CommandId::Move;
	}

	void setPoint(const Point &point)
	{
		this->point = point;
	}

	Point getPoint() const
	{
		return point;
	}

	void move()
	{
		std::cout << "Moving" << std::endl;
	}

private:
	Point point;
};

class DrawCommandResult : public AbstractCommandResult
{
public:
	DrawCommandResult() = delete;

	DrawCommandResult(CommandId id, CommandResult result)
	    : AbstractCommandResult(id, result)
	{
	}

	~DrawCommandResult() = default;
};

class MoveCommandResult : public AbstractCommandResult
{
public:
	MoveCommandResult() = delete;

	MoveCommandResult(CommandId id, CommandResult result)
	    : AbstractCommandResult(id, result)
	{
	}

	~MoveCommandResult() = default;
};

} // namespace dev::command

#endif // DRAWCOMMAND_H
