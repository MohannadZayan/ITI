#include "SystemInfo.h"
#include "ProcessManager.h"
#include "FileManager.h"
#include "NetworkManager.h"
#include "ThreadDemo.h"

#include <iostream>
#include <string>
#include <signal.h>


int main()
{
    // ? Creating objects for each manager class
    SystemInfo systemInfo;
    ProcessManager processManager;
    FileManager fileManager;
    NetworkManager networkManager;
    ThreadDemo threadDemo;


    int choice;


    // ? Keep displaying the menu until the user chooses 0
    while (true)
    {
        std::cout << "\n========================================\n";
        std::cout << "        LINUX SYSTEM MANAGER\n";
        std::cout << "========================================\n";


        std::cout << "\nSYSTEM\n";
        std::cout << " 1. System Information\n";
        std::cout << " 2. Memory Information\n";
        std::cout << " 3. Disk Information\n";


        std::cout << "\nPROCESSES\n";
        std::cout << " 4. List Processes\n";
        std::cout << " 5. Process Information\n";
        std::cout << " 6. Create Child Process\n";
        std::cout << " 7. Send Signal to Process\n";


        std::cout << "\nFILES\n";
        std::cout << " 8. File Information\n";
        std::cout << " 9. Change File Permissions\n";


        std::cout << "\nNETWORK\n";
        std::cout << "10. Network Information\n";
        std::cout << "11. Ping Host\n";
        std::cout << "12. DNS Lookup\n";


        std::cout << "\nTHREADS\n";
        std::cout << "13. Multi-Thread Demo\n";


        std::cout << "\n 0. Exit\n";


        std::cout << "\n========================================\n";
        std::cout << "Enter choice: ";
        std::cin >> choice;


        // ? Exit the program
        if (choice == 0)
        {
            std::cout << "Exiting Linux System Manager..."
                      << std::endl;

            break;
        }


        // ? SYSTEM INFORMATION
        switch (choice)
        {
            case 1:
            {
                systemInfo.displaySystemInfo();
                break;
            }


            case 2:
            {
                systemInfo.displayMemoryInfo();
                break;
            }


            case 3:
            {
                systemInfo.displayDiskInfo();
                break;
            }


            // ? PROCESS MANAGEMENT

            case 4:
            {
                processManager.listProcesses();
                break;
            }


            case 5:
            {
                int pid;

                std::cout << "Enter PID: ";
                std::cin >> pid;

                processManager.processInfo(pid);

                break;
            }


            case 6:
            {
                processManager.createChildProcess();
                break;
            }


            case 7:
            {
                int pid;
                int signalChoice;


                std::cout << "Enter PID: ";
                std::cin >> pid;


                std::cout << "\n1. SIGTERM\n";
                std::cout << "2. SIGSTOP\n";
                std::cout << "3. SIGCONT\n";
                std::cout << "4. SIGKILL\n";


                std::cout << "Choice: ";
                std::cin >> signalChoice;


                int signal;


                if (signalChoice == 1)
                {
                    signal = SIGTERM;
                }

                else if (signalChoice == 2)
                {
                    signal = SIGSTOP;
                }

                else if (signalChoice == 3)
                {
                    signal = SIGCONT;
                }

                else if (signalChoice == 4)
                {
                    signal = SIGKILL;
                }

                else
                {
                    std::cout << "Invalid signal choice."
                              << std::endl;

                    break;
                }


                processManager.sendSignal(pid, signal);

                break;
            }


            // ? FILE MANAGEMENT

            case 8:
            {
                std::string path;

                std::cout << "Enter file path: ";
                std::cin >> path;

                fileManager.fileInfo(path.c_str());

                break;
            }


            case 9:
            {
                std::string path;
                int permissions;


                std::cout << "Enter file: ";
                std::cin >> path;


                std::cout << "Enter permission: ";
                std::cin >> std::oct >> permissions >> std::dec;


                fileManager.changePermissions(
                    path.c_str(),
                    permissions
                );

                break;
            }


            // ? NETWORK MANAGEMENT

            case 10:
            {
                networkManager.networkInfo();
                break;
            }


            case 11:
            {
                std::string host;

                std::cout << "Enter host: ";
                std::cin >> host;

                networkManager.pingHost(host.c_str());

                break;
            }


            case 12:
            {
                std::string hostname;

                std::cout << "Enter hostname: ";
                std::cin >> hostname;

                networkManager.dnsLookup(hostname.c_str());

                break;
            }


            // ? THREAD DEMO

            case 13:
            {
                threadDemo.runDemo();
                break;
            }


            // ? Invalid menu choice

            default:
            {
                std::cout << "Invalid menu option."
                          << std::endl;

                break;
            }
        }
    }


    return 0;
}