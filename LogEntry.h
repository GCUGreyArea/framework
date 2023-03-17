// ==================================================================
// LogEntry.h
//
// NOTE: 
// ==================================================================
#ifndef __LOGENTRY_CLASS__
#define __LOGENTRY_CLASS__

#include "Base.h"
// #include "LoggerFactory.h"
#include "Log.h"

#include <istream>

class LogEntry : public Base {
    public:
        LogEntry();
        friend std::istream& operator>>(std::istream & is, LogEntry & le);
        friend std::ostream & operator<<(std::ostream & os, LogEntry & le);

    private:
        Log::e_LogLelvel_t logLevel;
        Date date;

        // Parser values
        std::string entryMk;
        int entry;
        std::string level;
        std::string msg;
};

#endif//__LOGENTRY_CLASS__

