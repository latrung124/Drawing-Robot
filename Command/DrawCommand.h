/*
* DrawCommand.h
* Author: Trung La
* Description: This file contains the DrawCommand class which is responsible for handling commands.
*/

#ifndef DRAWCOMMAND_H
#define DRAWCOMMAND_H

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

    CommandId id() const override {
        return CommandId::Draw;
    }

    virtual void draw() {
        // Draw
        std::cout << "Drawing" << std::endl;
    }
private:
    Line line;
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