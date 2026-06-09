#pragma once
#include <iostream>
#include <iomanip>
#include <windows.h>
#include <vector>

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

namespace CpuCalc {
	CpuSnapshot GetCpuTimes();
	double calculateCpuUsage(CpuSnapshot old, CpuSnapshot newer);
}