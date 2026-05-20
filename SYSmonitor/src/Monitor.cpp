#include <iostream>
#include <chrono>
#include "RamInfo.h"

void runStep();

int mains() {
	auto startTime = std::chrono::steady_clock::now();
	while (true) {
		auto now = std::chrono::steady_clock::now();
		if (now - startTime > std::chrono::seconds(1)) {
			runStep();
			startTime = std::chrono::steady_clock::now();
		}
	}
	return 0;
}
void runStep() {
	system("cls");
	RAMstats ram = RamInfo::getRamInfo();
	RamInfo::printInfo(ram);
}