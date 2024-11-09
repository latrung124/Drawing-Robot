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

    std::string deviceName() const override;
    uint16_t deviceID() const override;

    void start() override;
    void stop() override;

    void attachFeatures() override;
    void attachFeature(AbstractFeaturePtr&& feature);

private:
    std::map<uint16_t, AbstractFeaturePtr> m_features;
};

#endif // ROBOTICDEVICE_H