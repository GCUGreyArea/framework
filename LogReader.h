// ==================================================================
// LogReader.h
//
// NOTE: 
// ==================================================================
#ifndef __LOGREADER_CLASS__
#define __LOGREADER_CLASS__

#include "Base.h"
#include "Log.h"

class LogReader : public Base {
    public:
        LogReader();

        void readLogFile(const char * logFile);

    private:
        // TODO - Define private members
};

#endif//__LOGREADER_CLASS__

