/*
* DeviceHelper.h
* Author: Trung La
* Description: This file contains the DeviceHelper class which is responsible for handling devices.
*/

#include "RoboticDevice.h"
#include "DrawFeature.h"

namespace dev {

namespace helper {
    
namespace feature {

using DrawFeature = dev::feature::DrawFeature;
using AbstractFeature = dev::feature::AbstractFeature;

template <typename Feature, typename... Args>
void attachFeature(RoboticDevice &device, Args&&... args) {
    auto feature = std::make_shared<Feature>(std::forward<Args>(args)...);
    device.attachFeature(std::move(std::dynamic_pointer_cast<dev::feature::AbstractFeature>(feature)));
}

template <typename Handler, typename... Args>
void attachFeatureHandler(AbstractFeature &feature, Args&&... args) {
    auto handler = std::make_shared<Handler>(std::forward<Args>(args)...);
    feature.addHandler(std::move(std::dynamic_pointer_cast<dev::handler::AbstractHandler>(handler)));
}

} // namespace dev::helper::feature

} // namespace dev::helper

} // namespace dev