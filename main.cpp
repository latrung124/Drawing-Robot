#include <iostream>
#include <thread>
#include <chrono>
#include "DeviceHelper.h"
#include "DrawFeature.h"
#include <string>

std::mutex g_mutex;

int main() {
    std::cout << "Hello, World!" << std::endl;

    //Print thread id
    std::cout << "Main thread id: " << std::this_thread::get_id() << std::endl;
    //Start the robotic device
    RoboticDevice roboticDevice;
    dev::helper::feature::attachFeature<dev::feature::DrawFeature>(roboticDevice, roboticDevice.deviceName());

    //suspend the main thread for 10 seconds for attaching the debugger
    std::this_thread::sleep_for(std::chrono::seconds(10));

    roboticDevice.start();
    roboticDevice.run();
    roboticDevice.stop();

    return 0;
}
