#include "CpuInfo.h"
#include <chrono>
struct CpuSnapshot {
	ULONGLONG idle;
	ULONGLONG kernel;
	ULONGLONG user;
};

int main() {
	CpuSnapshot snapshot1 = GetCpuTimes();
	CpuSnapshot snapshot2 = GetCpuTimes();
	auto startTime = std::chrono::steady_clock::now();
	while (true) {
		auto now = std::chrono::steady_clock::now();
		if (now - startTime > std::chrono::milliseconds(300)) {
			
			startTime = std::chrono::steady_clock::now();
		}
	}
	return 0;

}

double calculateCpuUsage(CpuSnapshot old, CpuSnapshot newer) {
	if (newer.idle < old.idle || newer.kernel < old.kernel || newer.user < old.user) return 0;
	ULONGLONG deltaIdle = newer.idle - old.idle;
	ULONGLONG deltaKernel = newer.kernel - old.kernel;
	ULONGLONG deltaUser = newer.user - old.user;
	ULONGLONG total = deltaKernel + deltaUser;
	if (total == 0) return 0;
	ULONGLONG active = total - deltaIdle;
	return (static_cast<double>(active) / total) * 100.0;
}

CpuSnapshot GetCpuTimes() {
	FILETIME idleTime, kernelTime, userTime;
	GetSystemTimes(&idleTime, &kernelTime, &userTime);
	auto idle = (static_cast<ULONGLONG>(idleTime.dwHighDateTime) << 32 ) | idleTime.dwLowDateTime;
	auto kernel = (static_cast<ULONGLONG>(kernelTime.dwHighDateTime) << 32) | kernelTime.dwLowDateTime;
	auto user = (static_cast<ULONGLONG>(userTime.dwHighDateTime) << 32) | userTime.dwLowDateTime;
	return CpuSnapshot(idle, kernel, user);
}