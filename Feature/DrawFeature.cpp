/*
* DrawFeature.cpp
* Author: Trung La
* Description: This file contains the DrawFeature class which is responsible for drawing features.
*/

#include "DrawFeature.h"

namespace dev::feature {

DrawFeature::DrawFeature(const std::string &deviceName) : AbstractFeature(deviceName) {
}

void DrawFeature::addHandler(AbstractHandlerPtr&& handler) {
}

} // namespace dev::feature