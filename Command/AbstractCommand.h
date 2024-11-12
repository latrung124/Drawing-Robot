/*
* AbstractCommand.h
* Author: Trung La
* Description: This file contains the AbstractCommand class which is responsible for handling commands.
*/

#ifndef ABSTRACTCOMMAND_H
#define ABSTRACTCOMMAND_H

#include "CommandId.h"
#include <functional>
#include "AbstractCommandResult.h"

namespace dev::command {

class AbstractCommand {
public:
    using Callback = std::function<void(const AbstractCommandResult&)>;

    AbstractCommand() = default;
    virtual ~AbstractCommand() = default;
    virtual CommandId id() const = 0;

    void registerResultListener(Callback callback) {
        m_callback = callback;
    }

    void notifyCommandCompleted(const AbstractCommandResult &result) {
        if (m_callback) {
            m_callback(result);
        }
    }

private:
    Callback m_callback;
};

} // namespace dev::command

#endif // ABSTRACTCOMMAND_H