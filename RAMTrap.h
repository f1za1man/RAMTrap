#ifndef RAMTRAP_H
#define RAMTRAP_H

#include <string>
using namespace std;

class MemoryBlock 
{
    public:
        int id;
        bool isHoneypot;
        bool isInfected;

        MemoryBlock();
        MemoryBlock(int id, bool honeypot);
};

class Logger 
{
    public:
        void log(string message);
        string getTimestamp();
};

class Malware 
{
    protected:
        string type;
    public:
        Malware(string type);
        virtual void scanMemory(MemoryBlock memory[], int size, Logger& logger);
};

class AdvancedMalware : public Malware 
{
    public:
        AdvancedMalware();
        void scanMemory(MemoryBlock memory[], int size, Logger& logger) override;
};

#endif
