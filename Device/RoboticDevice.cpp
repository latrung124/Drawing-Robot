/*
* RoboticDevice.cpp
* Author: Trung La
* Description: This file contains the RoboticDevice class which is responsible for controlling robotic devices.
*/

#include "RoboticDevice.h"
#include "DeviceHelper.h"

void RoboticDevice::start() {
    // Start the robotic device
    startFeatures();
}

void RoboticDevice::stop() {
    // Stop the robotic device
    // Do some clean up stuff
    stopFeatures();
}

void RoboticDevice::startFeatures() {
    std::cout << "Starting features" << std::endl;
    for (auto& feature : m_features) {
        if (!feature.second) {
            std::cout << "feature was null! " << static_cast<uint16_t>(feature.first) << "\n";
            return;
        }
        feature.second->start();
    }
}

void RoboticDevice::stopFeatures() {
    std::cout << "Stop features" << std::endl;
    for (auto& feature : m_features) {
        if (!feature.second) {
            std::cout << "feature was null! " << static_cast<uint16_t>(feature.first) << "\n";
            return;
        }
        feature.second->stop();
    }
}

void RoboticDevice::run() {
    readInputFile();
}

bool RoboticDevice::readInputFile() {
    std::cout << "Reading input file" << std::endl;
    if (auto feature = getFeature<dev::feature::DrawFeature>(dev::feature::FeatureType::Draw); feature) {
        std::cout << feature->deviceName() << std::endl;
        if (auto fileHandler = feature->getHandler<dev::handler::FileHandler>(dev::handler::HandlerType::File); fileHandler) {
            int32_t fileId = fileHandler->openFile(std::string(SOURCE_DIR) + "/InputFiles/input.txt",
                                  dev::handler::OpenMode::ToRead);

            std::string line;
            while (std::getline(fileHandler->getFileHandle(fileId), line)) {
                std::cout << line << std::endl;
                sendCommand(line);
            }
            fileHandler->closeFile(fileId);
        }
    } else {
        std::cout << "Feature not found" << std::endl;
        return false;
    }

    return true;
}

void RoboticDevice::sendCommand(const std::string& command) {
    if (auto feature = getFeature<dev::feature::DrawFeature>(dev::feature::FeatureType::Draw); feature) {
        if (auto commandHandler = feature->getHandler<dev::handler::CommandHandler>(dev::handler::HandlerType::Command); commandHandler) {
            commandHandler->send(command.c_str());
        }
    }
}

template <class Feature>
std::shared_ptr<Feature> RoboticDevice::getFeature(dev::feature::FeatureType type) {
    if (type == dev::feature::FeatureType::None) {
        std::cout << "Feature type is None" << std::endl;
        return nullptr;
    }

    if (m_features.find(type) == m_features.end()) {
        std::cout << "Feature type not found" << std::endl;
        return nullptr;
    }

    return std::dynamic_pointer_cast<Feature>(m_features[type]);
}

std::string RoboticDevice::deviceName() const {
    return "RoboticDevice";
}

uint16_t RoboticDevice::deviceID() const {
    return 1;
}

void RoboticDevice::attachFeature(AbstractFeaturePtr&& feature) {
    dev::helper::feature::attachFeatureHandler<dev::handler::FileHandler>(*feature);
    dev::helper::feature::attachFeatureHandler<dev::handler::CommandHandler>(*feature);
    m_features[feature->featureType()] = std::move(feature);

    std::cout << "Feature attached" << std::endl;
}