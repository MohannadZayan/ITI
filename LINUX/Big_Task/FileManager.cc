#include "FileManager.h"
#include <sys/stat.h>
#include <string>
#include <iostream>


//* ========== FILE INFORMATION ==========


// ? This function displays information about a file

void FileManager::fileInfo(const char* path)
{
    // ? struct stat contains information about the file
    struct stat fileInfo;


    // ? stat() gets information about the file specified by the path
    if (stat(path, &fileInfo) == -1)
    {
        perror("stat");
        return;
    }


    // ? Outputs the size of the file in bytes
    std::cout << "File Size: "
              << fileInfo.st_size
              << " bytes"
              << std::endl;


    // ? Checking whether the path refers to a regular file
    if (S_ISREG(fileInfo.st_mode))
    {
        std::cout << "File Type: Regular File"
                  << std::endl;
    }


    // ? Checking whether the path refers to a directory
    else if (S_ISDIR(fileInfo.st_mode))
    {
        std::cout << "File Type: Directory"
                  << std::endl;
    }


    // ? Checking whether the path refers to a symbolic link
    else if (S_ISLNK(fileInfo.st_mode))
    {
        std::cout << "File Type: Symbolic Link"
                  << std::endl;
    }


    // ? If it is none of the types we explicitly check for
    else
    {
        std::cout << "File Type: Other"
                  << std::endl;
    }


    // ? Outputs the UID of the file owner
    std::cout << "Owner UID: "
              << fileInfo.st_uid
              << std::endl;


    // ? Outputs the GID of the group that owns the file
    std::cout << "Group GID: "
              << fileInfo.st_gid
              << std::endl;


    // ? Outputs the file permissions
    std::cout << "Permissions: "
              << std::oct
              << (fileInfo.st_mode & 0777)
              << std::dec
              << std::endl;
}



//* ========== CHANGE FILE PERMISSIONS ==========


// ? This function changes the permissions of a file

void FileManager::changePermissions(const char* path, int permissions)
{
    // ? chmod() changes the permissions of the file
    if (chmod(path, permissions) == -1)
    {
        perror("chmod");
        return;
    }


    // ? The permissions were changed successfully
    std::cout << "Permissions changed successfully."
              << std::endl;
}