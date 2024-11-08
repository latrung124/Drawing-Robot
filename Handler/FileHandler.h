/*
* FileHandler.h
* Author: Trung La
* Description: This file contains the FileHandler class which is responsible for reading and writing to files.
*/

#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <iostream>
#include <fstream>

namespace File {

using fstream = std::fstream;

constexpr uint16_t MAX_HANDLE_COUNT = 10;

enum class OpenMode {
    ToRead,
    ToWrite,
    ToReadWrite,
};

class FileHandler {
private:
    uint16_t m_maxHandleCount;
    uint16_t m_currentHandleIdx;

    fstream* m_handleIdxArr = nullptr;

public:
    FileHandler();
    ~FileHandler();

    int32_t openFile(const std::string& filePath, OpenMode mode);
    void closeFile(uint16_t handleIdx);

    fstream& getFileHandle(uint16_t handleIdx);
};

} // namespace File

#endif // FILEHANDLER_H