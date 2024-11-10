/*
* AbstractFeature.h
* Author: Trung La
* Description: This file contains the AbstractFeature class which is responsible for handling features.
*/

#ifndef ABSTRACTFEATURE_H
#define ABSTRACTFEATURE_H

#include "AbstractHandler.h"

namespace dev::feature {

enum class FeatureType : uint16_t {
    None,
    Draw,
};

class AbstractFeature {
public:
    AbstractFeature() = delete;
    explicit AbstractFeature(const std::string &deviceName) : m_deviceName(deviceName) {};
    virtual ~AbstractFeature() = default;

    using AbstractHandlerPtr = dev::handler::AbstractHandlerPtr;
    using HandlerType = dev::handler::HandlerType;

    virtual void start() = 0;
    virtual void stop() = 0;

    virtual FeatureType featureType() const = 0;
    virtual void addHandler(AbstractHandlerPtr&& handler) = 0;

    std::string deviceName() const {
        return m_deviceName;
    }

private:
    std::string m_deviceName;
};

using AbstractFeaturePtr = std::shared_ptr<AbstractFeature>;

} // namespace dev::feature

#endif // ABSTRACTFEATURE_H