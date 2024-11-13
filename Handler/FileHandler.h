/*
 * FileHandler.h
 * Author: Trung La
 * Description: This file contains the FileHandler class which is responsible for reading and
 * writing to files.
 */

#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <fstream>
#include <iostream>

#include "AbstractHandler.h"

namespace dev::handler {

constexpr uint16_t MAX_HANDLE_COUNT = 10;

enum class OpenMode
{
	ToRead,
	ToWrite,
	ToReadWrite,
};

class FileHandler;
using FileHandlerPtr = std::shared_ptr<FileHandler>;

using fstream = std::fstream;

class FileHandler : public AbstractHandler
{
private:
	uint16_t m_maxHandleCount;
	uint16_t m_currentHandleIdx;

	fstream *m_handleIdxArr = nullptr;

public:
	using AbstractHandler::AbstractHandler;
	using HandlerType = dev::handler::HandlerType;

	FileHandler();
	~FileHandler();

	void start() override;
	void stop() override;

	HandlerType type() const override
	{
		return HandlerType::File;
	}

	int32_t openFile(const std::string &filePath, OpenMode mode);
	void closeFile(uint16_t handleIdx);

	fstream &getFileHandle(uint16_t handleIdx) const;
};

} // namespace dev::handler

#endif // FILEHANDLER_H
