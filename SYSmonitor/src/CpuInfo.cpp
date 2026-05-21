#include "CpuInfo.h"

int main() {
	
}

float calculateCpuLoad()

float GetCpuTimes() {
	FILETIME idleTime, kernelTime, userTime;
	GetSystemTimes(&idleTime, &kernelTime, &userTime);
	auto var = (static_cast<ULONGLONG>(idleTime.dwHighDateTime) << 32 ) | idleTime.dwLowDateTime;

}