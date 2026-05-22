#include "CpuInfo.h"
#include <chrono>


int main() {
	auto now = std::chrono::steady_clock::now();
	while (true) {
		CpuSnapshot oldTimes = CpuCalc::GetCpuTimes();
		auto startTime = std::chrono::steady_clock::now();
		do {
			now = std::chrono::steady_clock::now();
		} while (now - startTime < std::chrono::milliseconds(500));
		CpuSnapshot newTimes = CpuCalc::GetCpuTimes();
		std::cout << CpuCalc::calculateCpuUsage(oldTimes, newTimes) << std::endl;
		do
		{
			now = std::chrono::steady_clock::now();
		} while (now - startTime < std::chrono::milliseconds(1000));
	}
}

namespace CpuCalc {
	double calculateCpuUsage(CpuSnapshot old, CpuSnapshot newer) {
		if (newer.idle < old.idle || newer.kernel < old.kernel || newer.user < old.user) return 0.0;
		ULONGLONG deltaIdle = newer.idle - old.idle;
		ULONGLONG deltaKernel = newer.kernel - old.kernel;
		ULONGLONG deltaUser = newer.user - old.user;
		ULONGLONG total = deltaKernel + deltaUser;
		if (total == 0 || total < deltaIdle) return 0.0;
		ULONGLONG active = total - deltaIdle;
		return (static_cast<double>(active) / total) * 100.0;
	}

	CpuSnapshot GetCpuTimes() {
		FILETIME idleTime, kernelTime, userTime;
		GetSystemTimes(&idleTime, &kernelTime, &userTime);
		auto idle = (static_cast<ULONGLONG>(idleTime.dwHighDateTime) << 32) | idleTime.dwLowDateTime;
		auto kernel = (static_cast<ULONGLONG>(kernelTime.dwHighDateTime) << 32) | kernelTime.dwLowDateTime;
		auto user = (static_cast<ULONGLONG>(userTime.dwHighDateTime) << 32) | userTime.dwLowDateTime;
		return CpuSnapshot(idle, kernel, user);
	}
}