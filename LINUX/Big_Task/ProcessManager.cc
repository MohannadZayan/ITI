#include "ProcessManager.h"
#include <filesystem>
#include <fstream>
#include <string>
#include <iostream>
#include <cctype>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>


// ? This is a struct unlike utsname, because /proc/<pid>/status contains a huge amount of info which we dont need
struct ProcessInfo
{
    int pid;
    std::string name;
    char state;
    int ppid;
    int threads;
    std::string vmSize;
    std::string vmRSS;
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



// * ========== PROCESS INFO ==========


// ? Given a PID, the function returns info about a specific process


void ProcessManager::processInfo(int pid) {
    std :: string statusPath = "/proc/" + std :: to_string(pid) + "/status";


    std :: ifstream file (statusPath);


    if (!file) {
        std :: cerr << "Failed to open info for PID:  " << pid << std :: endl;
        return;
    }


    ProcessInfo process{};


    process.pid = pid;


    std :: string label;


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


        else if (label == "Threads:")
        {
            file >> process.threads;
        }


        else if (label == "VmSize:")
        {
            std::string value;
            std::string unit;


            file >> value >> unit;


            process.vmSize = value + " " + unit;
        }


        else if (label == "VmRSS:")
        {
            std::string value;
            std::string unit;


            file >> value >> unit;


            process.vmRSS = value + " " + unit;
        }
    }


    std::cout << "\n========== PROCESS INFORMATION ==========\n";


    std::cout << "PID: " << process.pid << std::endl;
    std::cout << "PPID: " << process.ppid << std::endl;
    std::cout << "Name: " << process.name << std::endl;
    std::cout << "State: " << process.state << std::endl;
    std::cout << "Threads: " << process.threads << std::endl;
    std::cout << "Virtual Memory: " << process.vmSize << std::endl;
    std::cout << "Resident Memory: " << process.vmRSS << std::endl;


    std::cout << "=========================================\n";
}



// * ========== PROCESS CREATION ==========


// ? This function creates a new process


void ProcessManager::createChildProcess()
{
    // ? fork() creates a new child process
    pid_t pid = fork();


    // ? Checking if fork() failed
    if (pid == -1)
    {
        perror("fork");
        return;
    }


    // ? fork() returns 0 to the child process
    if (pid == 0)
    {
        std::cout << "\n========== CHILD PROCESS ==========\n";


        // ? getpid() returns the PID of the current process
        std::cout << "Child PID: "
                  << getpid() << std::endl;


        // ? getppid() returns the PID of the parent process
        std::cout << "Child PPID: "
                  << getppid() << std::endl;


        std::cout << "===================================\n";
    }


    // ? fork() returns the PID of the child to the parent process
    else
    {
        std::cout << "\n========== PARENT PROCESS ==========\n";


        // ? getpid() returns the PID of the current process
        std::cout << "Parent PID: "
                  << getpid() << std::endl;


        // ? The value returned by fork() is the child's PID
        std::cout << "Child PID: "
                  << pid << std::endl;


        std::cout << "====================================\n";
    }
}



// * ========== CHILD EXIT STATUS ==========


// ? This function creates a child process and allows the parent
// ? to wait for the child and check how it terminated


void ProcessManager::childExitStatus()
{
    // ? fork() creates a new child process
    pid_t pid = fork();


    // ? Checking if fork() failed
    if (pid == -1)
    {
        perror("fork");
        return;
    }


    // ? fork() returns 0 to the child process
    if (pid == 0)
    {
        // ? The child exits with status code 42
        std::cout << "Child process exiting with status 42..."
                  << std::endl;

        _exit(42);
    }


    // ? fork() returns the child's PID to the parent process
    else
    {
        int status;


        // ? waitpid() makes the parent wait for the specific child
        // ? until the child terminates
        if (waitpid(pid, &status, 0) == -1)
        {
            perror("waitpid");
            return;
        }


        // ? Checking if the child terminated normally
        if (WIFEXITED(status))
        {
            // ? WEXITSTATUS() retrieves the exit status returned by the child
            std::cout << "Child exited normally with status: "
                      << WEXITSTATUS(status)
                      << std::endl;
        }


        // ? Checking if the child was terminated by a signal
        else if (WIFSIGNALED(status))
        {
            // ? WTERMSIG() returns the signal that terminated the child
            std::cout << "Child was terminated by signal: "
                      << WTERMSIG(status)
                      << std::endl;
        }
    }
}



// * ========== PROCESS SIGNALS ==========


// ? This function sends a signal to a specific process

void ProcessManager::sendSignal(int pid, int signal)
{
    // ? kill() sends the specified signal to the specified process
    if (kill(pid, signal) == -1)
    {
        perror("kill");
        return;
    }


    // ? The signal was successfully sent
    std::cout << "Signal " << signal
              << " sent successfully to PID "
              << pid << std::endl;
}