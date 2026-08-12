#ifndef PROCESSMANAGER_H
#define PROCESSMANAGER_H

class ProcessManager {

    public: 
    void listProcesses ();
    void processInfo (int pid);
    void createChildProcess ();
    void childExitStatus ();
    void sendSignal (int pid, int signal);
};





#endif // PROCESSMANAGER_H