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
    uint16_t width;
    uint16_t height;
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

    Dimension getDimension() const {
        return m_dimension;
    }

private:
    Dimension m_dimension;
};

class DimensionCommandResult : public AbstractCommandResult {
public:
    DimensionCommandResult() = delete;
    DimensionCommandResult(CommandId id, CommandResult result)
        : AbstractCommandResult(id, result) {}
    ~DimensionCommandResult() = default;
};

} // namespace dev::command

#endif // DIMENSIONCOMMAND_H