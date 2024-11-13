#include "DeviceHelper.h"
#include "DrawFeature.h"
#include <chrono>
#include <iostream>
#include <string>
#include <thread>

int main()
{
	std::cout << "Hello, World!" << std::endl;

	// Print thread id
	std::cout << "Main thread id: " << std::this_thread::get_id() << std::endl;
	// Start the robotic device
	RoboticDevice roboticDevice;
	dev::helper::feature::attachFeature<dev::feature::DrawFeature>(
	    roboticDevice, roboticDevice.deviceName());

	// Suspend the main thread 10 seconds for attaching the debugger
	std::this_thread::sleep_for(std::chrono::seconds(10));

	roboticDevice.start();
	roboticDevice.run();

	return 0;
}
