/*
* AbstractCommandResult.h
* Author: Trung La
* Description: This file contains the AbstractCommandResult class which is responsible for handling command results.
*/

#ifndef ABSTRACTCOMMANDRESULT_H
#define ABSTRACTCOMMANDRESULT_H

#include "CommandId.h"

namespace dev::command {

enum class CommandResult : uint16_t {
    None,
    Success,
    Failure,
};

class AbstractCommandResult {
public:
    AbstractCommandResult() = delete;
    AbstractCommandResult(CommandId id, CommandResult result)
        : m_id(id), m_result(result) {}
    virtual ~AbstractCommandResult() = default;
    virtual CommandResult result() const {
        return m_result;
    }

    virtual CommandId id() const {
        return m_id;
    }

private:
    CommandId m_id;
    CommandResult m_result;
};

} // namespace dev::command

#endif // ABSTRACTCOMMANDRESULT_H