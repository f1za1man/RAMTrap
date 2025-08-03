#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include "RAMTrap.h"
using namespace std;


MemoryBlock::MemoryBlock() {}

MemoryBlock::MemoryBlock(int id, bool honeypot) 
{
    this->id = id;
    isHoneypot = honeypot;
    isInfected = false;
}

// --- Logger Methods ---
void Logger::log(string message) 
{
    cout << "[" << getTimestamp() << "] " << message << endl;
}

string Logger::getTimestamp() 
{
    time_t now = time(0); // Get current time
    char buffer[20];
    strftime(buffer, sizeof(buffer), "%H:%M:%S", localtime(&now)); // Format the time
    return string(buffer); // Return the formatted time as a string
}

// --- Malware Methods ---
Malware::Malware(string type)
{
    this->type = type;
}

void Malware::scanMemory(MemoryBlock memory[], int size, Logger& logger) 
{
    logger.log(type + " scan started.");
    for (int i = 0; i < size; i++) 
    {
        memory[i].isInfected = true;
        logger.log(type + " infected Block " + to_string(memory[i].id));

        if (memory[i].isHoneypot) 
        {
            logger.log("!!! ALERT: Honeypot triggered at Block " + to_string(memory[i].id));
            break;
        }
    }
    logger.log(type + " scan completed.");
}

// Constructor of AdvancedMalware that sets type to "AdvancedMalware" in the base class
AdvancedMalware::AdvancedMalware() : Malware("AdvancedMalware") {}

void AdvancedMalware::scanMemory(MemoryBlock memory[], int size, Logger& logger) 
{
    logger.log(type + " smart scan started.");
    for (int i = 0; i < size; i++) 
    {
        if (!memory[i].isHoneypot) 
        {
            memory[i].isInfected = true;
            logger.log(type + " infected Block " + to_string(memory[i].id));
        }
    }
    logger.log(type + " smart scan completed. Honeypots bypassed.");
}

// --- Helper to check honeypot index ---
bool isHoneypotIndex(int index, int honeypotIndexes[], int count) 
{
    for (int i = 0; i < count; i++) 
    {
        if (honeypotIndexes[i] == index)
            return true;
    }
    return false;
}

// --- Main Function ---
int main() 
{
    srand(time(0));
    Logger logger;

    const int blockCount = 10;
    const int honeypotCount = 2;
    int honeypotIndexes[honeypotCount];
    int placed = 0;

    // Generate unique honeypot indexes
    while (placed < honeypotCount) 
    {
        int index = rand() % blockCount;
        if (!isHoneypotIndex(index, honeypotIndexes, placed)) 
        {
            honeypotIndexes[placed++] = index;
        }
    }

    // Initialize memory
    MemoryBlock memory[blockCount];
    for (int i = 0; i < blockCount; i++) 
    {
        bool isHoneypot = isHoneypotIndex(i, honeypotIndexes, honeypotCount);
        memory[i] = MemoryBlock(i, isHoneypot);
    }

    logger.log("RAM Trap initialized with 10 blocks and 2 honeypots.");

    Malware basic("BasicMalware");
    basic.scanMemory(memory, blockCount, logger);

    AdvancedMalware adv;
    adv.scanMemory(memory, blockCount, logger);

    logger.log("Final Memory Status:");
    for (int i = 0; i < blockCount; i++) 
    {
        cout << "Block " << setw(2) << memory[i].id
             << " | Infected: " << boolalpha << memory[i].isInfected
             << " | Honeypot: " << memory[i].isHoneypot << endl;
    }

    return 0;
}
