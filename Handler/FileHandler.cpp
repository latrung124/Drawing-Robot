/*
 * FileHandler.cpp
 * Author: Trung La
 * Description: This file contains the implementation of the FileHandler class which is responsible
 * for reading and writing to files.
 */

#include "FileHandler.h"

namespace dev::handler {

FileHandler::FileHandler()
    : m_maxHandleCount(MAX_HANDLE_COUNT)
    , m_currentHandleIdx(0)
    , m_handleIdxArr(new std::fstream[m_maxHandleCount])
{
}

FileHandler::~FileHandler()
{
	stop();
}

void FileHandler::start()
{
	// Start the file handler
	std::cout << "File handler started!" << std::endl;
}

void FileHandler::stop()
{
	// Stop the file handler
	for (auto i = 0; i < m_maxHandleCount; ++i) {
		if (m_handleIdxArr[i].is_open()) {
			m_handleIdxArr[i].close();
		}
	}

	delete[] m_handleIdxArr;
	std::cout << "File handler stopped!" << std::endl;
}

int32_t FileHandler::openFile(const std::string &filePath, OpenMode mode)
{
	if (m_currentHandleIdx >= m_maxHandleCount) {
		std::cerr << "Cannot open more files. Maximum number of files reached." << std::endl;
		return -1;
	}

	auto &fileHandle = m_handleIdxArr[m_currentHandleIdx];
	if (fileHandle.is_open()) {
		fileHandle.close();
		std::cerr << "File handle is already open. Closing the file." << std::endl;
		return m_currentHandleIdx++;
	}

	switch (mode) {
	case OpenMode::ToRead: {
		fileHandle.open(filePath, std::ios::in);
		break;
	}
	case OpenMode::ToWrite: {
		fileHandle.open(filePath, std::ios::out);
		break;
	}
	case OpenMode::ToReadWrite: {
		fileHandle.open(filePath, std::ios::in | std::ios::out);
		break;
	}
	default: {
		std::cerr << "Invalid open mode." << std::endl;
		return -1;
	}
	}

	if (!fileHandle.is_open()) {
		std::cerr << "Cannot open file: " << filePath << std::endl;
		return -1;
	}

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
		std::cout << "File id: " << handleIdx << " closed!" << std::endl;
	} else {
		std::cerr << "File id: " << handleIdx << " is not open!" << std::endl;
	}
}

fstream &FileHandler::getFileHandle(uint16_t handleIdx) const
{
	if (handleIdx >= m_maxHandleCount || handleIdx < 0) {
		throw std::out_of_range("Invalid handle index.");
	}

	return m_handleIdxArr[handleIdx];
}

} // namespace dev::handler
