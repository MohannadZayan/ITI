#include "ProcessManager.h"
#include <filesystem>
#include <fstream>
#include <string>
#include <iostream>
#include <cctype>

// ? This is a struct unlike utsname, because /proc/<pid>/status contains a huge amount of info which we dont need
struct ProcessInfo
{
    int pid;
    std::string name;
    char state;
    int ppid;
};


//* ========== LIST PROCESSES ==========

void ProcessManager::listProcesses()
{
    // ? We are iterating over all the files in /proc
    for (const auto& entry : std::filesystem::directory_iterator("/proc"))
    {
        // ? Getting the filename
        std::string pidString =
            entry.path().filename().string();

            //? assuming the filename is a number
        bool numeric = true;

        // ? Checking every character
        for (char c : pidString)
        {
            if (!std::isdigit(c))
            {
                // ? if it is numeric, then break
                numeric = false;
                break;
            }
        }
        // ? Ignore the non-process entries
        if (!numeric)
        {
            continue;
        }


        ProcessInfo process{};
        // ? Converting the PID string to an integer
        process.pid = std::stoi(pidString);

        // ? Buiulding the path to the status file
        std::string statusPath =
            "/proc/" + pidString + "/status";   // ! Here for example if the PID is 1234 then the status file is /proc/1234/status

            // ? Opening the status file
        std::ifstream file(statusPath);

        // ? Verifying that the file could be opened
        if (!file)
        {
            continue;
        }

        std::string label;
// ? Finding "name", "state" and "ppid" in the file
        while (file >> label)
        {
            if (label == "Name:")
            {
                file >> process.name;
            }

            else if (label == "State:")
            {
                file >> process.state;
            }

            else if (label == "PPid:")
            {
                file >> process.ppid;
            }
        }

        // ? Finally, printing the info

        std::cout << "PID: " << process.pid
                  << " | Name: " << process.name
                  << " | State: " << process.state
                  << " | PPID: " << process.ppid
                  << std::endl;
    }
}