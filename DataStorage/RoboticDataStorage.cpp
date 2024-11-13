/*
 * RoboticDataStorage.cpp
 * Author: Trung La
 * Description: This file contains the RoboticDataStorage class which is responsible for storing
 * robotic data.
 */

#include "RoboticDataStorage.h"

namespace dev::data {

RoboticDataStorage::RoboticDataStorage()
    : m_data({})
{
}

void RoboticDataStorage::storeData(const RoboticData &data)
{
	m_data = data;
}

RoboticData RoboticDataStorage::getData() const
{
	return m_data;
}

} // namespace dev::data
