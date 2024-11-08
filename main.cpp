#include "Handler/FileHandler.h"
#include <string>

int main() {
    std::cout << "Hello, World!" << std::endl;
    File::FileHandler fileHandler;
    int32_t readFileId = fileHandler.openFile(std::string(SOURCE_DIR) + "/InputFiles/input.txt",
     File::OpenMode::ToRead);
    int32_t writeFileId = fileHandler.openFile(std::string(SOURCE_DIR) + "/InputFiles/output.txt",
     File::OpenMode::ToWrite);

    std::string line;
    while (std::getline(fileHandler.getFileHandle(readFileId), line)) {
        fileHandler.getFileHandle(writeFileId) << line << std::endl;
    }

    fileHandler.closeFile(readFileId);
    fileHandler.closeFile(writeFileId);

    return 0;
}
