#include <iostream>
#include <chrono>
#include "RamInfo.h"
#include "CpuInfo.h"
#define LOG(x) std::cout << x << std::endl

std::vector<CoreInfo> coresInfo = getCpuTopo();
void runStep();

int main() {
	auto startTime = std::chrono::steady_clock::now();
	auto now = std::chrono::steady_clock::now();
	while (true) {
		CpuSnapshot oldTimes = CpuCalc::GetCpuTimes();
		auto startTime = std::chrono::steady_clock::now();
		do {
			now = std::chrono::steady_clock::now();
		} while (now - startTime < std::chrono::milliseconds(500));
		CpuSnapshot newTimes = CpuCalc::GetCpuTimes();
		runStep();
		LOG("\nCPU:");
		CpuCalc::printThreadsandCores();
		std::cout << "Usage: " << CpuCalc::calculateCpuUsage(oldTimes, newTimes) << "%" << std::endl;
		do
		{
			now = std::chrono::steady_clock::now();
		} while (now - startTime < std::chrono::milliseconds(1000));
	}0;
}
void runStep() {
	system("cls");
	LOG("RAM:");
	RAMstats ram = RamInfo::getRamInfo();
	RamInfo::printInfo(ram);
}