#pragma once
#include <iostream>
#include <iomanip>
#include <windows.h>

struct CpuSnapshot {
	ULONGLONG idle;
	ULONGLONG kernel;
	ULONGLONG user;
};

namespace CpuCalc {
	CpuSnapshot GetCpuTimes();
	double calculateCpuUsage(CpuSnapshot old, CpuSnapshot newer);
}