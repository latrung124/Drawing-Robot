/*
* RoboticDataStorage.cpp
* Author: Trung La
* Description: This file contains the RoboticDataStorage class which is responsible for storing robotic data.
*/

#include "RoboticDataStorage.h"

namespace dev::data {

RoboticDataStorage::RoboticDataStorage()
    : m_data({})
{
}

void RoboticDataStorage::storeData(const RoboticData& data) {
    std::cout << "Storing data!" << std::endl;
    std::cout << "Position: " << data.pos.x << ", " << data.pos.y << std::endl;
    std::cout << "Map2D: " << data.map2D.width << ", " << data.map2D.height << std::endl;
    m_data = data;
}

RoboticData RoboticDataStorage::getData() const {
    return m_data;
}

} // namespace dev::data