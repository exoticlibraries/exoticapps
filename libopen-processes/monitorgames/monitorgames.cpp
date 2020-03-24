/**
    \copyright Copyright (c) 2020, Adewale Azeez 
    \author Adewale Azeez <azeezadewale98@gmail.com>
    \date 24 March 2020
    \file monitorgames.cpp
*/

#define USE_HACKY_PROCESSES_MONITOR

#include <libopen/processes.h>
#include <iostream>
#include <pthread.h>
#include <list>
#include <fstream>

using namespace libopen;

void ProcessStatusChange(PROCESS process, void* extraParam)
{
    if (process.status == PROCESS_STATUS::STARTED)
    {
        std::cout << (process.windowTitle.size() > 0 ? process.windowTitle : process.exeName) << " has started running" << std::endl;
        
    } else if (process.status == PROCESS_STATUS::STOPPED)
    {
        std::cout << (process.windowTitle.size() > 0 ? process.windowTitle : process.exeName) << " has stopped running" << std::endl;
    }
    
}

void *FindProcess(void *processPath)
{
    const char* name;
    name = (const char*)processPath;
    Hacky_MonitorProcessPath(name, &ProcessStatusChange, NULL);
    return NULL;
}

int main() 
{
#ifdef USE_HACKY_PROCESSES_MONITOR
    std::vector<std::string> processes_to_monitor;
    int i;
    int rc;
    int count = 0;
    std::ifstream input( "./games_name_part.txt" );
    
    for( std::string line; getline( input, line ); )
    {
        processes_to_monitor.push_back(line);
        count++;
    }
    for( i = 0; i < count; i++ ) 
    {
        pthread_t thread;
        rc = pthread_create(&thread, NULL, FindProcess, (void*)processes_to_monitor[i].c_str());
        
        if (rc) {
            std::cerr << "cannot monitor process " << processes_to_monitor[i] << std::endl;
            return -1;
        }
    }
    pthread_exit(NULL);
    
#endif
    return 0;
}

// Win: g++ monitorgames.cpp -lpsapi -lopen-processes -lpthread -o monitorgames