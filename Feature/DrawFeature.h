/*
* DrawFeature.h
* Author: Trung La
* Description: This file contains the DrawFeature class which is responsible for drawing features.
*/

#ifndef DRAWFEATURE_H
#define DRAWFEATURE_H

#include "FileHandler.h"
#include "CommandHandler.h"
#include "AbstractFeature.h"

namespace dev::feature {

class DrawFeature : public AbstractFeature {
public:
    DrawFeature() = delete;
    explicit DrawFeature(const std::string &deviceName);
    virtual ~DrawFeature() = default;

    using AbstractHandlerPtr = dev::handler::AbstractHandlerPtr;
    using FileHandlerPtr = dev::handler::FileHandlerPtr;
    using CommandHandlerPtr = dev::handler::CommandHandlerPtr;

    FeatureType featureType() const override {
        return FeatureType::DRAW;
    }

    void addHandler(AbstractHandlerPtr&& handler) override;

private:
    FileHandlerPtr m_fileHandler;
    CommandHandlerPtr m_commandHandler;
};

} // namespace dev::feature

#endif // DRAWFEATURE_H