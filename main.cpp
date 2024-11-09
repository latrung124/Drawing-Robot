#include "Handler/FileHandler.h"
#include "Device/RoboticDevice.h"
#include <string>

int main() {
    std::cout << "Hello, World!" << std::endl;
    dev::handler::FileHandler fileHandler(10);
    int32_t readFileId = fileHandler.openFile(std::string(SOURCE_DIR) + "/InputFiles/input.txt",
     dev::handler::OpenMode::ToRead);
    int32_t writeFileId = fileHandler.openFile(std::string(SOURCE_DIR) + "/InputFiles/output.txt",
     dev::handler::OpenMode::ToWrite);

    std::string line;
    while (std::getline(fileHandler.getFileHandle(readFileId), line)) {
        fileHandler.getFileHandle(writeFileId) << line << std::endl;
    }

    fileHandler.closeFile(readFileId);
    fileHandler.closeFile(writeFileId);

    //Start the robotic device
    RoboticDevice roboticDevice;
    roboticDevice.start();
    roboticDevice.stop();

    return 0;
}
