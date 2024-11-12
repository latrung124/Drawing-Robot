/*
* RoboticDataStorage.h
* Author: Trung La
* Description: This file contains the RoboticDataStorage class which is responsible for storing robotic data.
*/

#ifndef ROBOTICDATASTORAGE_H
#define ROBOTICDATASTORAGE_H

#include <iostream>
#include <vector>

#include "AbstractDataStorage.h"

namespace dev::data {

struct StandPosition {
    int x = 0;
    int y = 0;
};

struct Map2D {
    int width = 0;
    int height = 0;
    std::vector<std::vector<uint16_t>> data{};
};

struct RoboticData {
    StandPosition pos{};
    Map2D map2D{};
};

class RoboticDataStorage : public AbstractDataStorage {
public:
    RoboticDataStorage();
    ~RoboticDataStorage() override = default;

    DataStorageType type() const override {
        return DataStorageType::RoboticDataStorage;
    }

    void storeData(const RoboticData& data);
    RoboticData getData() const;

private:
    RoboticData m_data;
};

} // namespace dev::data

#endif // ROBOTICDATASTORAGE_H