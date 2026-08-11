#include "SystemInfo.h"
#include <sys/utsname.h>
#include <fstream>
#include <string>
#include <iostream>


  //*  ========== SYSTEM INFO ==========

void SystemInfo :: displaySystemInfo () {

    // ! Initially contains sysname, nodename, release, version, machine from sys/utsname.h
    struct utsname systemInfo;

    if (uname(&systemInfo) == -1) {
        perror("uname");
        return;
    }
// ? Outputs the name of the operating system
    std :: cout << "Operating System: " << systemInfo.sysname << std :: endl;
// ? Outputs the name of the node on which the code is executing
    std :: cout << "Hostname: " << systemInfo.nodename << std :: endl;
// ? Outputs the release of the operating system
    std :: cout << "Kernel Version: " << systemInfo.release << std :: endl;
// ? Outputs the hardware platform on which the code is executing
    std :: cout << "Architecture: " << systemInfo.machine << std :: endl;
}

//* ========= MEMORY INFO ==========

void SystemInfo :: displayMemoryInfo () {

    // ? /proc is a special filesystem provided by linux that exposes info about the running system and its processes
    // ? /proc/meminfo is a file that contains information about the system's memory
    // ? ifstream file opens the file

    std:: ifstream file ("/proc/meminfo");
// ? Checking whether the file could be opened
    if (!file) {
        std :: cerr<< "Failed to open /proc/meminfo" << std :: endl;
        return;
    }
// ? We have these 3 variables because memory in one line is like "MemTotal 164231321 Kb"
    std:: string label;
    long long value;
    std :: string unit;
// ? Keep reading 3 pieces at a time while the file is still open
    while (file >> label >> value >> unit) {
        if (label == "MemTotal:") {
            std :: cout << "Total Memory: " << value << " " << unit << std :: endl;
        }

        else if (label == "MemAvailable:") {
            std :: cout << "Available Memory: " << value << " " << unit << std :: endl;
        }
    }
}
