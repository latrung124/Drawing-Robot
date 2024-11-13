/*
 * DrawFeature.h
 * Author: Trung La
 * Description: This file contains the DrawFeature class which is responsible for drawing features.
 */

#ifndef DRAWFEATURE_H
#define DRAWFEATURE_H

#include <map>

#include "AbstractFeature.h"
#include "CommandHandler.h"
#include "FileHandler.h"

namespace dev::feature {

using AbstractHandlerPtr = dev::handler::AbstractHandlerPtr;
using FileHandlerPtr = dev::handler::FileHandlerPtr;
using CommandHandlerPtr = dev::handler::CommandHandlerPtr;
using HandlerType = dev::handler::HandlerType;

class DrawFeature : public AbstractFeature
{
public:
	DrawFeature() = delete;
	explicit DrawFeature(const std::string &deviceName);
	virtual ~DrawFeature() = default;

	FeatureType featureType() const override
	{
		return FeatureType::Draw;
	}

	void start() override;
	void stop() override;

	void addHandler(AbstractHandlerPtr &&handler) override;

	template<class Handler = dev::handler::AbstractHandler>
	std::shared_ptr<Handler> getHandler(HandlerType type) const;

private:
	std::map<HandlerType, AbstractHandlerPtr> m_handlerMap;
};

template<class Handler>
std::shared_ptr<Handler> DrawFeature::getHandler(HandlerType type) const
{
	auto it = m_handlerMap.find(type);
	if (it != m_handlerMap.end()) {
		return std::dynamic_pointer_cast<Handler>(it->second);
	}
	return nullptr;
}

} // namespace dev::feature

#endif // DRAWFEATURE_H
