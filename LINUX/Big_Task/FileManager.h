#ifndef FILEMANAGER_H
#define FILEMANAGER_H

class FileManager
{
public:

    void fileInfo(const char* path);
    void changePermissions(const char* path, int permissions);

};

#endif