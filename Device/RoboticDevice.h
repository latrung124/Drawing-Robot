/*
* RoboticDevice.h
* Author: Trung La
* Description: This file contains the RoboticDevice class which is responsible for controlling robotic devices.
*/

#ifndef ROBOTICDEVICE_H
#define ROBOTICDEVICE_H

#include <map>

#include "AbstractDevice.h"
#include "AbstractFeature.h"

class RoboticDevice : public AbstractDevice {
public:
    RoboticDevice() = default;
    virtual ~RoboticDevice() = default;

    using AbstractFeaturePtr = dev::feature::AbstractFeaturePtr;
    using FeatureType = dev::feature::FeatureType;

    std::string deviceName() const override;
    uint16_t deviceID() const override;

    void start() override;
    void stop() override;
    void run() override;

    void attachFeature(AbstractFeaturePtr&& feature);

    template <class Feature = dev::feature::AbstractFeature>
    std::shared_ptr<Feature> getFeature(FeatureType type);

private:
    void startFeatures();
    void stopFeatures();
    bool readInputFile();
    void sendCommand(const std::string& command);

    std::map<FeatureType, AbstractFeaturePtr> m_features;
};

#endif // ROBOTICDEVICE_H