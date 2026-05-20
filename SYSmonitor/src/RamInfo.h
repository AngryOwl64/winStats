#pragma once
#include <iostream>
#include <iomanip>
#include <windows.h>
struct RAMstats {
	DWORDLONG totalPhysRam;
	DWORDLONG totalAvailRam;
};
namespace RamInfo {
	RAMstats getRamInfo();
	double toGB(DWORDLONG inBytes);
	double getUsed(RAMstats info);
	double getUsedPercent(RAMstats info);
	void printInfo(RAMstats info);
}