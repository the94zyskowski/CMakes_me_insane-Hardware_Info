#include <iostream>
#ifdef _WIN32
#include <windows.h>
#elif __linux__
#include <unistd.h>
#include <sys/sysinfo.h>
#endif

int main() {
    std::cout << "System info:" << std::endl;

#ifdef _WIN32
    char computerName[MAX_COMPUTERNAME_LENGTH + 1];
    DWORD size = sizeof(computerName) / sizeof(computerName[0]);
    GetComputerNameA(computerName, &size);
    std::cout << "Host name: " << computerName << std::endl;

    SYSTEM_INFO sysInfo;
    GetSystemInfo(&sysInfo);
    std::cout << "CPU count: " << sysInfo.dwNumberOfProcessors << std::endl;

    MEMORYSTATUSEX statex;
    statex.dwLength = sizeof(statex);
    GlobalMemoryStatusEx(&statex);
    std::cout << "RAM: " << statex.ullTotalPhys / (1024 * 1024) << " MB" << std::endl;
#elif __linux__
    char hostname[1024];
    hostname[1023] = '\0';
    gethostname(hostname, 1023);
    std::cout << "Host name: " << hostname << std::endl;

    long numProcs = sysconf(_SC_NPROCESSORS_ONLN);
    std::cout << "CPU count: " << numProcs << std::endl;

    struct sysinfo memInfo;
    sysinfo(&memInfo);
    long long totalVirtualMem = memInfo.totalram;
    totalVirtualMem += memInfo.totalswap;
    totalVirtualMem *= memInfo.mem_unit;
    std::cout << "RAM: " << memInfo.totalram / (1024 * 1024) << " MB" << std::endl;
#else
    std::cout << "OS not supported." << std::endl;
#endif

    return 0;
}
