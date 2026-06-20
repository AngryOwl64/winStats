#pragma once
#pragma comment(lib, "ntdll.lib")
#include <iostream>
#include <iomanip>
#include <windows.h>
#include <vector>
#include <winternl.h>

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
	void printThreadsandCores();
	CpuSnapshot GetCpuTimes();
	double calculateCpuUsage(CpuSnapshot old, CpuSnapshot newer);
}