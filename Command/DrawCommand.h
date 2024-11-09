/*
* DrawCommand.h
* Author: Trung La
* Description: This file contains the DrawCommand class which is responsible for handling commands.
*/

#ifndef DRAWCOMMAND_H
#define DRAWCOMMAND_H

#include "AbstractCommand.h"

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

    virtual void draw() = 0;
};

class DrawLineCommand : public DrawCommand {
public:
    DrawLineCommand() = default;
    ~DrawLineCommand() = default;

    virtual void draw() override {
        // Draw line
        std::cout << "Drawing line" << std::endl;
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
};

} // namespace dev::command

#endif // DRAWCOMMAND_H