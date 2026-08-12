#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

class NetworkManager
{
public:

    void networkInfo();
    void pingHost(const char* host);
    void dnsLookup(const char* hostname);

};

#endif