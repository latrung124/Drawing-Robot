/*
 * FileHandler.cpp
 * Author: Trung La
 * Description: This file contains the implementation of the FileHandler class which is responsible for reading and writing to files.
 */

#include "FileHandler.h"

namespace dev::handler {

FileHandler::FileHandler()
    : m_maxHandleCount(MAX_HANDLE_COUNT),
      m_currentHandleIdx(0),
      m_handleIdxArr(new std::fstream[m_maxHandleCount])
{
}

FileHandler::~FileHandler()
{
    delete[] m_handleIdxArr;
}

void FileHandler::start()
{
    // Start the file handler
    std::cout << "File handler started!" << std::endl;
}

void FileHandler::stop()
{
    // Stop the file handler
    std::cout << "File handler stopped!" << std::endl;
}

int32_t FileHandler::openFile(const std::string& filePath, OpenMode mode) {

    if (m_currentHandleIdx >= m_maxHandleCount) {
        std::cerr << "Cannot open more files. Maximum number of files reached." << std::endl;
        return -1;
    }

    if (m_handleIdxArr[m_currentHandleIdx].is_open()) {
        m_handleIdxArr[m_currentHandleIdx].close();
        std::cerr << "File handle is already open. Closing the file." << std::endl;
        return m_currentHandleIdx++;
    }

    switch(mode) {
        case OpenMode::ToRead: {
            m_handleIdxArr[m_currentHandleIdx].open(filePath, std::ios::in);
            break;
        }
        case OpenMode::ToWrite: {
            m_handleIdxArr[m_currentHandleIdx].open(filePath, std::ios::out);
            break;
        }
        case OpenMode::ToReadWrite: {
            m_handleIdxArr[m_currentHandleIdx].open(filePath, std::ios::in | std::ios::out);
            break;
        }
        default: {
            std::cerr << "Invalid open mode." << std::endl;
            return -1;
        }
    }

    if (!m_handleIdxArr[m_currentHandleIdx].is_open()) {
        std::cerr << "Cannot open file: " << filePath << std::endl;
        return -1;
    }
    std::cout << "File id: " << m_currentHandleIdx  << " opened!" << std::endl;
    return m_currentHandleIdx++;
}

void FileHandler::closeFile(uint16_t handleIdx)
{
    if (handleIdx >= m_maxHandleCount) {
        std::cerr << "Invalid handle index." << std::endl;
        return;
    }

    if (m_handleIdxArr[handleIdx].is_open()) {
        m_handleIdxArr[handleIdx].close();
        std::cout << "File id: " << handleIdx  << " closed!" << std::endl;
    }
}

fstream& FileHandler::getFileHandle(uint16_t handleIdx)
{
    return m_handleIdxArr[handleIdx];
}

} // namespace File

