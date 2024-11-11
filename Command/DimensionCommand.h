/*
* DimensionCommand.h
* Author: Trung La
* Description: This file contains the DimensionCommand class which is responsible for handling commands.
*/

#ifndef DIMENSIONCOMMAND_H
#define DIMENSIONCOMMAND_H

#include "AbstractCommand.h"

namespace dev::command {

struct Dimension {
    int width;
    int height;
};

class DimensionCommand : public AbstractCommand {
public:
    DimensionCommand() : m_dimension({0, 0}) {}
    DimensionCommand(const Dimension& dimension) : m_dimension(dimension) {}
    ~DimensionCommand() = default;

    virtual CommandId id() const {
        return CommandId::Dimension;
    }

    void setDimension(const Dimension& dimension) {
        m_dimension = dimension;
    }

private:
    Dimension m_dimension;
};

} // namespace dev::command

#endif // DIMENSIONCOMMAND_H