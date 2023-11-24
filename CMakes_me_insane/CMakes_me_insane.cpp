#include <iostream>
// Conditional compilation depending on the operating system
#ifdef _WIN32 // For Windows systems
#include <windows.h> // Includes the Windows-specific headers for system calls
#elif __linux__ // For Linux systems
#include <unistd.h> // Provides access to the POSIX operating system API
#include <sys/sysinfo.h> // For the sysinfo structure and system call
#endif

int main() {
    std::cout << "System info:" << std::endl;

    // Windows-specific code block
#ifdef _WIN32
    // Declare buffer to store the computer name
    char computerName[MAX_COMPUTERNAME_LENGTH + 1];
    // Compute the size of the buffer
    DWORD size = sizeof(computerName) / sizeof(computerName[0]);
    // Get the computer name and store it in computerName buffer
    GetComputerNameA(computerName, &size);
    // Output the computer name
    std::cout << "Host name: " << computerName << std::endl;

    // Declare a SYSTEM_INFO structure to store system information
    SYSTEM_INFO sysInfo;
    // Retrieve the system information
    GetSystemInfo(&sysInfo);
    // Output the number of processors
    std::cout << "CPU count: " << sysInfo.dwNumberOfProcessors << std::endl;

    // Declare a MEMORYSTATUSEX structure to store memory status information
    MEMORYSTATUSEX statex;
    // Set the size of the structure before using it
    statex.dwLength = sizeof(statex);
    // Retrieve the memory status
    GlobalMemoryStatusEx(&statex);
    // Output the total physical memory (RAM) in MB
    std::cout << "RAM: " << statex.ullTotalPhys / (1024 * 1024) << " MB" << std::endl;

    // Linux-specific code block
#elif __linux__
    // Declare buffer to store the host name
    char hostname[1024];
    // Ensure the string is null-terminated
    hostname[1023] = '\0';
    // Get the host name and store it in hostname buffer
    gethostname(hostname, 1023);
    // Output the host name
    std::cout << "Host name: " << hostname << std::endl;

    // Get the number of online processors
    long numProcs = sysconf(_SC_NPROCESSORS_ONLN);
    // Output the number of online processors
    std::cout << "CPU count: " << numProcs << std::endl;

    // Declare a sysinfo structure to store system information
    struct sysinfo memInfo;
    // Retrieve the system information
    sysinfo(&memInfo);
    // Calculate the total virtual memory by adding RAM and swap space, then converting to bytes
    long long totalVirtualMem = memInfo.totalram;
    totalVirtualMem += memInfo.totalswap;
    totalVirtualMem *= memInfo.mem_unit;
    // Output the total physical memory (RAM) in MB
    std::cout << "RAM: " << memInfo.totalram / (1024 * 1024) << " MB" << std::endl;
#else
    // Message for unsupported operating systems
    std::cout << "OS not supported." << std::endl;
#endif

    return 0;
}
