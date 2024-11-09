/*
* AbstractHandler.h
* Author: Trung La
* Description: This file contains the AbstractHandler class which is responsible for handling commands.
*/

#ifndef ABSTRACTHANDLER_H
#define ABSTRACTHANDLER_H

#include <memory>
#include <string>

namespace dev::handler {

enum class HandlerType : uint16_t {
    None,
    File,
    Command,
};

class AbstractHandler {

public:
    AbstractHandler() = default;
    virtual ~AbstractHandler() = default;

    virtual HandlerType type() const = 0;

private:
};

using AbstractHandlerPtr = std::shared_ptr<AbstractHandler>;

} // namespace dev::handler

#endif // ABSTRACTHANDLER_H