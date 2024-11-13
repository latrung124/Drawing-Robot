/*
 * DrawFeature.cpp
 * Author: Trung La
 * Description: This file contains the DrawFeature class which is responsible for drawing features.
 */

#include "DrawFeature.h"

namespace dev::feature {

DrawFeature::DrawFeature(const std::string &deviceName)
    : AbstractFeature(deviceName)
{
}

void DrawFeature::start()
{
	std::cout << "DrawFeature started" << std::endl;
	for (auto &item : m_handlerMap) {
		if (auto handler = item.second; handler) {
			handler->start();
		} else {
			std::cerr << "Null handler found in start method" << std::endl;
		}
	}
}

void DrawFeature::stop()
{
	std::cout << "DrawFeature stopped" << std::endl;
	for (auto &item : m_handlerMap) {
		if (auto handler = item.second; handler) {
			handler->stop();
		} else {
			std::cerr << "Null handler found in stop method" << std::endl;
		}
	}
}

void DrawFeature::addHandler(AbstractHandlerPtr &&handler)
{
	if (!handler) {
		std::cerr << "Attempted to add a null handler" << std::endl;
		return;
	}

	m_handlerMap[handler->type()] = std::move(handler);
}

} // namespace dev::feature
