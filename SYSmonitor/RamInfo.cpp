#include <iostream>
#include <iomanip>
#include <windows.h>

struct RAMstats {
	DWORDLONG totalPhysRam;
	DWORDLONG totalAvailRam;
};

RAMstats getRamInfo();
double toGB(DWORDLONG inBytes);
double getUsed(RAMstats info);
double getUsedProcent(RAMstats info);
void printInfo(RAMstats info);

int main() {
	auto test = getRamInfo();
	printInfo(test);
}

RAMstats getRamInfo() {
	MEMORYSTATUSEX memInfo;
	memInfo.dwLength = sizeof(MEMORYSTATUSEX); 
	GlobalMemoryStatusEx(&memInfo);
	return RAMstats(memInfo.ullTotalPhys, memInfo.ullAvailPhys);
}

double toGB(DWORDLONG inBytes) {
	return (((inBytes / 1024.0) / 1024) / 1024);
}

double getUsed(RAMstats info) {
	if (info.totalAvailRam > info.totalPhysRam) return 0.0;
	return static_cast<double>(info.totalPhysRam - info.totalAvailRam);
}

double getUsedProcent(RAMstats info) {
	return (static_cast<double>(info.totalPhysRam - info.totalAvailRam) / info.totalPhysRam) * 100.0;
}

void printInfo(RAMstats info) {
	std::cout << std::fixed << std::setprecision(1);
	std::cout << "Total: " << toGB(info.totalPhysRam) << "GB" << std::endl;
	std::cout << "Available: " << toGB(info.totalAvailRam) << "GB" << std::endl;
	std::cout << "used: " << toGB(getUsed(info)) << "GB" << std::endl;
	std::cout << "in Procent: " << getUsedProcent(info) << "%\n";
}