/*
* DrawFeature.cpp
* Author: Trung La
* Description: This file contains the DrawFeature class which is responsible for drawing features.
*/

#include "DrawFeature.h"

namespace dev::feature {

DrawFeature::DrawFeature(const std::string &deviceName) : AbstractFeature(deviceName) {
}

void DrawFeature::start() {
    std::cout << "DrawFeature started" << std::endl;
    for(auto& handler : m_handlerMap) {
        handler.second->start();
    }
}

void DrawFeature::stop() {
    std::cout << "DrawFeature stopped" << std::endl;
    for(auto& handler : m_handlerMap) {
        handler.second->stop();
    }
}

void DrawFeature::addHandler(AbstractHandlerPtr&& handler) {
    m_handlerMap[handler->type()] = std::move(handler);
}

} // namespace dev::feature