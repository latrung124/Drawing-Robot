/*
* DrawFeature.h
* Author: Trung La
* Description: This file contains the DrawFeature class which is responsible for drawing features.
*/

#ifndef DRAWFEATURE_H
#define DRAWFEATURE_H

#include <map>

#include "FileHandler.h"
#include "CommandHandler.h"
#include "AbstractFeature.h"

namespace dev::feature {

using AbstractHandlerPtr = dev::handler::AbstractHandlerPtr;
using FileHandlerPtr = dev::handler::FileHandlerPtr;
using CommandHandlerPtr = dev::handler::CommandHandlerPtr;
using HandlerType = dev::handler::HandlerType;

class DrawFeature : public AbstractFeature {
public:
    DrawFeature() = delete;
    explicit DrawFeature(const std::string &deviceName);
    virtual ~DrawFeature() = default;

    FeatureType featureType() const override {
        return FeatureType::Draw;
    }

    void start() override;
    void stop() override;

    void addHandler(AbstractHandlerPtr&& handler) override;

    template<class Handler = dev::handler::AbstractHandler>
    std::shared_ptr<Handler> getHandler(HandlerType type) {
        if (type == HandlerType::None) {
            std::cout << "Handler type is None" << std::endl;
            return nullptr;
        }

        if (m_handlerMap.find(type) == m_handlerMap.end()) {
            std::cout << "Handler type not found" << std::endl;
            return nullptr;
        }

        return std::dynamic_pointer_cast<Handler>(m_handlerMap[type]);
    }

private:
    std::map<HandlerType, AbstractHandlerPtr> m_handlerMap;
};

} // namespace dev::feature

#endif // DRAWFEATURE_H