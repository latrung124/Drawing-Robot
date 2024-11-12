/*
* AbstractDataStorage.h
* Author: Trung La
* Description: This file contains the AbstractDataStorage class which is responsible for storing data.
*/

#ifndef ABSTRACTDATASTORAGE_H
#define ABSTRACTDATASTORAGE_H

namespace dev::data {

enum class DataStorageType {
    None = 0,
    RoboticDataStorage,
};

class AbstractDataStorage {
public:
    AbstractDataStorage() = default;
    virtual ~AbstractDataStorage() = default;

    virtual DataStorageType type() const {
        return DataStorageType::None;
    }
};

} // namespace dev::data

#endif // ABSTRACTDATASTORAGE_H