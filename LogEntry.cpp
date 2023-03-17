/**
 * @file LogEntry.cpp
 * @author Barry Robinson (barry.robinson@alertlogic.com)
 * @brief 
 * @version 1.0
 * @date 29-11-2021
 * 
 * @copyright Copyright (c) Alert Logic 2021
 * 
 */
#include <iostream>
#include <string>

// // Support libraries gts kernel development
// #include <support.h>

#include "LogEntry.h"

LogEntry::LogEntry() : Base("LogEntry"),
                       date(Date::DATE_NUM_FMAT) {}


std::istream& operator>>(std::istream& is, LogEntry& le) {
    std::string sep;
    if(is >> le.entryMk >> le.entry >> sep >> le.level >> sep >> le.date) {
       le.logLevel = Log::logLevelFromString(le.level);
        std::string remaining;

        getline(is, remaining);

        // Get rig of the formating brackets...
        unsigned int i=0;
        while(remaining[i++] != '[') {}

        // unsigned int leIdx=0;
        while(remaining[i] != ']') {
            le.msg += remaining[i++];
        }
    }

    return is;
}

std::ostream & operator<<(std::ostream & os, LogEntry & le) {
    os << "[Entry No: " << le.entry << " / Level: " << le.logLevel << " / date: " << le.date << " / message: " << le.msg << "]";

    return os;
}
