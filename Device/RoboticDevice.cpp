/*
* RoboticDevice.cpp
* Author: Trung La
* Description: This file contains the RoboticDevice class which is responsible for controlling robotic devices.
*/

#include "RoboticDevice.h"
#include "DeviceHelper.h"

void RoboticDevice::start() {
    // Start the robotic device
    attachFeatures();
}

void RoboticDevice::stop() {
    // Stop the robotic device
    // Do some clean up stuff
}

std::string RoboticDevice::deviceName() const {
    return "RoboticDevice";
}

uint16_t RoboticDevice::deviceID() const {
    return 1;
}

void RoboticDevice::attachFeatures() {
    dev::helper::feature::attachFeature<dev::feature::DrawFeature>(*this, deviceName());
}

void RoboticDevice::attachFeature(AbstractFeaturePtr&& feature) {
    dev::helper::feature::attachFeatureHandler<dev::handler::FileHandler>(*feature);
    dev::helper::feature::attachFeatureHandler<dev::handler::CommandHandler>(*feature);
    m_features[static_cast<uint16_t>(feature->featureType())] = std::move(feature);

    std::cout << "Feature attached" << std::endl;
}