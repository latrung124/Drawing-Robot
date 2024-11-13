/*
 * AbstractDevice.h
 * Author: Trung La
 * Description: This file contains the AbstractDevice class which is responsible for reading and
 * writing to devices.
 */

#ifndef ABSTRACTDEVICE_H
#define ABSTRACTDEVICE_H

#include <string>

class AbstractDevice
{
public:
	AbstractDevice() = default;
	virtual ~AbstractDevice() = default;

	virtual std::string deviceName() const = 0;
	virtual uint16_t deviceID() const = 0;

	virtual void start() = 0;
	virtual void stop() = 0;

	virtual void run() = 0;
};

#endif // ABSTRACTDEVICE_H
