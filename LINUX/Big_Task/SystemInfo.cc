#include "SystemInfo.h"
#include <sys/utsname.h>
#include <sys/statvfs.h>
#include <fstream>
#include <string>
#include <iostream>


  //*  ========== SYSTEM INFO ==========

void SystemInfo :: displaySystemInfo () {

    // ! Initially contains sysname, nodename, release, version, machine from sys/utsname.h
    // ? uname is a linux API that returns info about the system
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


// * ========= DISK INFO ==========
void SystemInfo :: displayDiskInfo () {

    // ? statvfs is another linux API which gives us info about a filesystem

    //! struct statvfs initially contains 4 things:
    // ! f_blocks : Total blocks
    // ! f_bfree : Number of free blocks
    // ! f_bavail : Number of blocks available to an unpriviliged user
    // ! f_frsize : The size of each filesystem block in bytes

    struct statvfs diskInfo;

    // ? Here we are passing 2 things, the filesystem/path we're interested in ("/") and ("&diskInfo") which is the address of the structure where linux should put the found results
    if (statvfs ("/", &diskInfo) == -1 ) {
        perror ("statvfs");
        return;
    }
    // ? Total space
    unsigned long long totalBytes = diskInfo.f_blocks * diskInfo.f_frsize;

    //? Free space
    unsigned long long freeBytes = diskInfo.f_bfree * diskInfo.f_frsize;

    // ? Used space
    unsigned long long usedBytes = totalBytes - freeBytes;

    double totalGB =static_cast<double>(totalBytes) / (1024 * 1024 * 1024);

    double freeGB =static_cast<double>(freeBytes) / (1024 * 1024 * 1024);

    double usedGB =static_cast<double>(usedBytes) / (1024 * 1024 * 1024);

    std :: cout << "Total Disk Space: " << totalGB << " GB" << std :: endl;
    std :: cout << "Free Used Disk Space: " << freeGB << " GB" << std :: endl;
    std :: cout << "Used Disk Space: " << usedGB << " GB" << std :: endl;
}   
