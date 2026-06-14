#pragma once
#include <iostream>
#include <iomanip>
#include <windows.h>
#include <vector>
#include <winternl.h>

typedef struct _SYSTEM_PROCESSOR_PERFORMANCE_INFORMATION {
	LARGE_INTEGER IdleTime;
	LARGE_INTEGER KernelTime;
	LARGE_INTEGER UserTime;
	LARGE_INTEGER DpcTime;
	LARGE_INTEGER InterruptTime;
	ULONG InterruptCount;
} SYSTEM_PROCESSOR_PERFORMANCE_INFORMATION;

struct CoreInfo {
	WORD group;
	std::vector<int> logicProcessors;
};

struct CpuSnapshot {
	ULONGLONG idle;
	ULONGLONG kernel;
	ULONGLONG user;
};

std::vector<CoreInfo> getCpuTopo();
std::vector<CpuSnapshot> getLogicalCoreTimes();

namespace CpuCalc {
	CpuSnapshot GetCpuTimes();
	double calculateCpuUsage(CpuSnapshot old, CpuSnapshot newer);
}