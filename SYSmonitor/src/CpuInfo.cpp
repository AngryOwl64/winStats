#include "CpuInfo.h"
#include <chrono>

#define LOG(x) std::cout << x << std::endl;

int main() {
	auto now = std::chrono::steady_clock::now();
	SingleCore();
	while (true) {
		CpuSnapshot oldTimes = CpuCalc::GetCpuTimes();
		auto startTime = std::chrono::steady_clock::now();
		do {
			now = std::chrono::steady_clock::now();
		} while (now - startTime < std::chrono::milliseconds(500));
		CpuSnapshot newTimes = CpuCalc::GetCpuTimes();
		//std::cout << CpuCalc::calculateCpuUsage(oldTimes, newTimes) << std::endl;
		do
		{
			now = std::chrono::steady_clock::now();
		} while (now - startTime < std::chrono::milliseconds(1000));
	}
}

int SingleCore() {
	std::vector<CoreInfo> coresInfo;
	LOGICAL_PROCESSOR_RELATIONSHIP type = RelationProcessorCore;
	DWORD length = 0;
	GetLogicalProcessorInformationEx(type, NULL, &length);
	if (length == 0) return 0;
	std::vector<byte> buffer(length);
	auto var = GetLogicalProcessorInformationEx(type, reinterpret_cast<PSYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX>(buffer.data()), &length);
	if (var) {
		BYTE* ptr = buffer.data();
		BYTE* end = buffer.data() + length;
		while (ptr < end) {
			auto info = reinterpret_cast<PSYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX>(ptr);
			if (info->Relationship == RelationProcessorCore) {
				CoreInfo core;
				LOG("LOG: core successfully found");
				for (size_t i{}; i < info->Processor.GroupCount; i++) {
					auto groupMask = info->Processor.GroupMask[i];
					core.group = groupMask.Group;
					auto mask = groupMask.Mask;
					for (int bit{}; bit < 64; bit++) {
						if (mask & (1ull << bit)) {
							std::cout << "Logischer CPU CORE: " << bit << std::endl;
							core.logicProcessors.push_back(bit);
						}
					}

					std::cout << "Group: " << groupMask.Group << std::endl;
					std::cout << "Mask: " << groupMask.Mask << std::endl;
				}
				coresInfo.push_back(core);
			}
			ptr += info->Size;
		}
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