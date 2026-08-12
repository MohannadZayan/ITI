#include "NetworkManager.h"
#include <ifaddrs.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <netdb.h>
#include <string>
#include <iostream>
#include <net/if.h>


//* ========== NETWORK INFORMATION ==========


// ? The task requires us to display information about the available network interfaces
// ? For each IPv4 interface, we need:
// ? 1. Interface Name
// ? 2. IPv4 Address
// ? 3. Interface State
// ? The task specifically asks us to investigate getifaddrs() and inet_ntop()


void NetworkManager::networkInfo()
{
    // ? ifaddrs is a linked list containing information about network interfaces
    struct ifaddrs* interfaces = nullptr;


    // ? getifaddrs() gets information about all available network interfaces
    if (getifaddrs(&interfaces) == -1)
    {
        perror("getifaddrs");
        return;
    }


    // ? We iterate through every network interface in the linked list
    for (struct ifaddrs* current = interfaces;
         current != nullptr;
         current = current->ifa_next)
    {
        // ? Some interfaces may not have an address
        // ? We ignore those interfaces
        if (current->ifa_addr == nullptr)
        {
            continue;
        }


        // ? The task requires IPv4 interfaces
        // ? AF_INET represents an IPv4 address
        if (current->ifa_addr->sa_family != AF_INET)
        {
            continue;
        }


        // ? sockaddr_in contains the IPv4 address
        struct sockaddr_in* address =
            reinterpret_cast<struct sockaddr_in*>(current->ifa_addr);


        // ? This array will store the IPv4 address in readable form
        char ipAddress[INET_ADDRSTRLEN];


        // ? inet_ntop() converts the binary IPv4 address
        // ? into a human-readable string such as 192.168.1.10
        if (inet_ntop(AF_INET,
                      &address->sin_addr,
                      ipAddress,
                      INET_ADDRSTRLEN) == nullptr)
        {
            continue;
        }


        // ? Displaying the interface name required by the task
        std::cout << "Interface: "
                  << current->ifa_name
                  << std::endl;


        // ? Displaying the IPv4 address required by the task
        std::cout << "IP: "
                  << ipAddress
                  << std::endl;


        // ? IFF_UP tells us whether the interface is currently up
        if (current->ifa_flags & IFF_UP)
        {
            // ? Interface is active
            std::cout << "State: UP"
                      << std::endl;
        }
        else
        {
            // ? Interface is not active
            std::cout << "State: DOWN"
                      << std::endl;
        }


        std::cout << "-----------------------------------"
                  << std::endl;
    }


    // ? getifaddrs() allocates memory for the interface list
    // ? freeifaddrs() releases that memory
    freeifaddrs(interfaces);
}



//* ========== PING HOST ==========


// ? The task requires the user to enter a hostname or IP address
// ? and perform a basic ping
// ? The task specifically says NOT to use system("ping ...")
// ? Instead, we must investigate:
// ? fork()
// ? exec()
// ? waitpid()


void NetworkManager::pingHost(const char* host)
{
    // ? fork() creates a child process
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
        // ? The child process will execute the Linux ping program
        // ? -c 3 tells ping to send 3 packets
        execlp("ping",
               "ping",
               "-c",
               "3",
               host,
               (char*)nullptr);


        // ? If execlp() returns, the command failed
        // ? Normally exec() does not return if it succeeds
        perror("execlp");
        _exit(1);
    }


    // ? fork() returns the child's PID to the parent process
    else
    {
        int status;


        // ? The parent waits for the child process to finish
        // ? This satisfies the task requirement to investigate waitpid()
        if (waitpid(pid, &status, 0) == -1)
        {
            perror("waitpid");
            return;
        }


        // ? Checking whether the ping process finished normally
        if (WIFEXITED(status))
        {
            // ? WEXITSTATUS() gets the exit code returned by ping
            std::cout << "Ping process exited with status: "
                      << WEXITSTATUS(status)
                      << std::endl;
        }


        // ? Checking whether the ping process was terminated by a signal
        else if (WIFSIGNALED(status))
        {
            // ? WTERMSIG() tells us which signal terminated the process
            std::cout << "Ping process was terminated by signal: "
                      << WTERMSIG(status)
                      << std::endl;
        }
    }
}



//* ========== DNS LOOKUP ==========


// ? The task requires the user to enter a hostname
// ? and display its IP address
// ? The task asks us to investigate:
// ? getaddrinfo()
// ? getnameinfo()


void NetworkManager::dnsLookup(const char* hostname)
{
    // ? addrinfo contains information about the address returned by getaddrinfo()
    struct addrinfo hints{};

    struct addrinfo* result = nullptr;


    // ? We are looking specifically for IPv4 addresses
    hints.ai_family = AF_INET;


    // ? getaddrinfo() resolves the hostname into an IP address
    int status = getaddrinfo(hostname,
                             nullptr,
                             &hints,
                             &result);


    // ? Checking if the DNS lookup failed
    if (status != 0)
    {
        std::cerr << "DNS lookup failed: "
                  << gai_strerror(status)
                  << std::endl;

        return;
    }


    // ? sockaddr_in contains the IPv4 address returned by getaddrinfo()
    struct sockaddr_in* address =
        reinterpret_cast<struct sockaddr_in*>(result->ai_addr);


    // ? This array will store the IP address in readable form
    char ipAddress[INET_ADDRSTRLEN];


    // ? inet_ntop() converts the binary IPv4 address
    // ? into a human-readable IP address
    if (inet_ntop(AF_INET,
                  &address->sin_addr,
                  ipAddress,
                  INET_ADDRSTRLEN) == nullptr)
    {
        perror("inet_ntop");

        // ? Freeing the memory allocated by getaddrinfo()
        freeaddrinfo(result);

        return;
    }


    // ? Displaying the hostname entered by the user
    std::cout << "Hostname: "
              << hostname
              << std::endl;


    // ? Displaying the IP address found by the DNS lookup
    std::cout << "IP Address: "
              << ipAddress
              << std::endl;


    // ? Freeing the memory allocated by getaddrinfo()
    freeaddrinfo(result);
}