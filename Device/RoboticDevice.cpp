/*
* RoboticDevice.cpp
* Author: Trung La
* Description: This file contains the RoboticDevice class which is responsible for controlling robotic devices.
*/

#include "RoboticDevice.h"
#include "DeviceHelper.h"
#include "image_converter.h"

void RoboticDevice::start() {
    // Start the robotic device
    isDeviceRunning = true;
    m_dataStorage = std::make_shared<dev::data::RoboticDataStorage>();
    startFeatures();
    attachDataStorage(m_dataStorage);
}

void RoboticDevice::stop() {
    // Stop the robotic device
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
    if (readInputFile()) {
        std::cout << "Command count: " << m_commandCount << std::endl;
    }

    std::cout << "Robotic device is running" << std::endl;
    std::unique_lock<std::mutex> lock(m_mutex);
    m_commandCV.wait(lock, [this] { return m_commandCount == 0 || !isDeviceRunning; });
    //stop the device
    stop();
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
                m_commandCount++;
            }
            fileHandler->closeFile(fileId);
        } else {
            std::cerr << "File handler not found" << std::endl;
            return false;
        }
    } else {
        std::cout << "Feature not found" << std::endl;
        return false;
    }

    return true;
}

void RoboticDevice::writeOutputFile() {
    //create a thread that detach for writing output file
    std::cout << "Writing output file" << std::endl;
    std::thread writer([this]() {
        if (auto feature = getFeature<dev::feature::DrawFeature>(dev::feature::FeatureType::Draw); feature) {
            if (auto fileHandler = feature->getHandler<dev::handler::FileHandler>(dev::handler::HandlerType::File); fileHandler) {
                int32_t fileImageId = fileHandler->openFile(std::string(SOURCE_DIR) + "/OutputFiles/output.bmp",
                                      dev::handler::OpenMode::ToWrite);
                int32_t fileTextId = fileHandler->openFile(std::string(SOURCE_DIR) + "/OutputFiles/output.txt",
                                      dev::handler::OpenMode::ToWrite);                                      

                if (auto roboticData = std::dynamic_pointer_cast<dev::data::RoboticDataStorage>(m_dataStorage); roboticData) {
                    image_converter::image_converter converter;
                    auto gridBytes = converter.gridToImageBytes(roboticData->getData().map2D.data);
                    image_converter::image_converter::image_16bit_data image;
                    image.width = roboticData->getData().map2D.width;
                    image.height = roboticData->getData().map2D.height;
                    image.size = image.width * image.height * sizeof(uint16_t);
                    image.data = gridBytes;

                    auto bytes = converter.createImage(image);
                    std::string textResult = "";
                    for (auto& row : roboticData->getData().map2D.data) {
                        for (auto& col : row) {
                            textResult += std::to_string(col) + " ";
                        }
                        textResult += "\n";
                    }
                    fileHandler->getFileHandle(fileTextId).write(textResult.c_str(), textResult.size());
                    fileHandler->getFileHandle(fileImageId).write(reinterpret_cast<const char*>(bytes.data()), bytes.size());
                } else {
                    std::cerr << "Robotic data storage not found" << std::endl;
                }
                isDeviceRunning = false;
                fileHandler->closeFile(fileImageId);
                std::cout << "Output file written" << std::endl;
            } else {
                std::cerr << "File handler not found" << std::endl;
            }
        }
    });

    if (writer.joinable()) {
        writer.join();
    }
}

void RoboticDevice::sendCommand(const std::string& command) {
    if (auto feature = getFeature<dev::feature::DrawFeature>(dev::feature::FeatureType::Draw); feature) {
        if (auto commandHandler = feature->getHandler<dev::handler::CommandHandler>(dev::handler::HandlerType::Command); commandHandler) {
            auto callBack = [this](const dev::command::AbstractCommandResult& result) {
                std::cout << "Command completed with result: " << static_cast<uint16_t>(result.result()) << std::endl;
                std::lock_guard<std::mutex> lock(m_mutex);
                if (--m_commandCount == 0) {
                    writeOutputFile();
                    m_commandCV.notify_one();
                }
            };
            commandHandler->send(command.c_str(), callBack);
        } else {
            std::cerr << "Command handler not found" << std::endl;
        }
    } else {
        std::cerr << "Draw Feature not found" << std::endl;
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

void RoboticDevice::attachDataStorage(const std::weak_ptr<AbstractDataStorage>& dataStorage) {
    for (auto& feature : m_features) {
        if (!feature.second) {
            return;   
        }

        if (feature.second->featureType() != dev::feature::FeatureType::Draw) {
            continue;
        }

        auto drawFeature = std::dynamic_pointer_cast<dev::feature::DrawFeature>(feature.second);

        if (auto commandHandler = drawFeature->getHandler<dev::handler::CommandHandler>(dev::handler::HandlerType::Command); commandHandler) {
            commandHandler->setDataStorage(dataStorage);
        }
    }
}

std::weak_ptr<dev::data::AbstractDataStorage> RoboticDevice::dataStorage() {
    return m_dataStorage;
}