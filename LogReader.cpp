// ==================================================================
// LogReader.cpp
//
// NOTE: 
// ==================================================================

#include <iostream>
#include <sstream>
#include <string>

// Support libraries gts kernel development
// #include <support.h>

#include "LogReader.h"
#include "LogEntry.h"

LogReader::LogReader() : Base("LogReader") {}


void LogReader::readLogFile(const char * logFile) {
    std::ifstream ifs;

    ifs.open(logFile, std::ifstream::in);
    std::string line;
    
    while(getline(ifs,line)) {
        std::istringstream ss(line);

        LogEntry l;
        
        if(ss >> l) {
            std::cout << l << std::endl;
        }
    }
}