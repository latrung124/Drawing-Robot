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

struct Point {
    int x;
    int y;
};

struct Line {
    std::vector<Point> points;
};

class DrawCommand : public AbstractCommand {
public:
    DrawCommand() = default;
    ~DrawCommand() = default;

    virtual CommandId id() const = 0;

    virtual void draw() = 0;
};

class DrawLineCommand : public DrawCommand {
public:
    DrawLineCommand() : m_line({}) {};
    DrawLineCommand(const Line& line) {
        m_line.points.assign(line.points.begin(), line.points.end());
    };
    ~DrawLineCommand() = default;

    CommandId id() const override {
        return CommandId::DrawLine;
    }

    void setLine(const Line& line) {
        m_line.points.assign(line.points.begin(), line.points.end());
    }

    void draw() {
        // Draw
        std::cout << "Drawing line" << std::endl;
    }

private:
    Line m_line;
};

class DrawCircleCommand : public DrawCommand {
public:
    DrawCircleCommand() = default;
    ~DrawCircleCommand() = default;

    CommandId id() const override {
        return CommandId::DrawCircle;
    }

    void draw() {
        // Draw
        std::cout << "Drawing circle" << std::endl;
    }
};

class MoveCommand : public AbstractCommand {
public:
    MoveCommand() = default;
    ~MoveCommand() = default;

    CommandId id() const override {
        return CommandId::Move;
    }

    void move() {
        // Move
        std::cout << "Moving" << std::endl;
    }

private:
    Point point;
};

class DrawCommandResult : public AbstractCommandResult {
public:
    DrawCommandResult() = delete;
    DrawCommandResult(CommandId id, CommandResult result)
        : AbstractCommandResult(id, result) {}
    ~DrawCommandResult() = default;

    CommandResult result() const override {
        return m_result;
    }
};

class MoveCommandResult : public AbstractCommandResult {
public:
    MoveCommandResult() = delete;
    MoveCommandResult(CommandId id, CommandResult result)
        : AbstractCommandResult(id, result) {}
    ~MoveCommandResult() = default;

    CommandResult result() const override {
        return m_result;
    }
};

} // namespace dev::command

#endif // DRAWCOMMAND_H