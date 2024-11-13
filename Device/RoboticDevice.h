/*
 * RoboticDevice.h
 * Author: Trung La
 * Description: This file contains the RoboticDevice class which is responsible for controlling
 * robotic devices.
 */

#ifndef ROBOTICDEVICE_H
#define ROBOTICDEVICE_H

#include <condition_variable>
#include <map>
#include <mutex>
#include <thread>

#include "AbstractDevice.h"
#include "AbstractFeature.h"
#include "RoboticDataStorage.h"

class RoboticDevice : public AbstractDevice
{
public:
	RoboticDevice() = default;
	virtual ~RoboticDevice() = default;

	using AbstractFeaturePtr = dev::feature::AbstractFeaturePtr;
	using FeatureType = dev::feature::FeatureType;
	using AbstractDataStorage = dev::data::AbstractDataStorage;

	std::string deviceName() const override;
	uint16_t deviceID() const override;

	void start() override;
	void stop() override;
	void run() override;

	void attachFeature(AbstractFeaturePtr &&feature);
	void attachDataStorage(const std::weak_ptr<AbstractDataStorage> &dataStorage);

	template<class Feature = dev::feature::AbstractFeature>
	std::shared_ptr<Feature> getFeature(FeatureType type);

	std::weak_ptr<AbstractDataStorage> dataStorage();

private:
	void startFeatures();
	void stopFeatures();
	bool readInputFile();
	void writeOutputFile();

	void sendCommand(const std::string &command);

	std::map<FeatureType, AbstractFeaturePtr> m_features;
	std::shared_ptr<AbstractDataStorage> m_dataStorage;

	std::mutex m_mutex;
	std::condition_variable m_commandCV;

	int m_commandCount = 0;
	bool isDeviceRunning = false;
};

#endif // ROBOTICDEVICE_H
