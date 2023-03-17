/**
 * @file Log.cpp
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

#include "Log.h"
// #include "LoggerFactory.h"

Log::Log() :
    Base("Log"),
    mLogName(DEFAULT_LOG_FILE),
    mDate(Date::DATE_NUM_FMAT),
    mLevel(DEFAULT_LOG_LEVEL),
    mMaxSize(DEFAULT_LOG_SIZE),
    mEntries(0) {
        setLastEntry();
}

Log::Log(const char * logName, e_LogLelvel_t level, int maxLogSize) :
    Base("Log"),
    mLogName(logName),
    mLevel(level),
    mMaxSize(maxLogSize),
    mEntries(0) {
        setLastEntry();
}

Log::Log(const char * logName, e_LogLelvel_t level) :
    Base("Log"),
    mLogName(logName),
    mLevel(level),
    mMaxSize(DEFAULT_LOG_SIZE),
    mEntries(0) {
        // mOut.open(mLogName,std::ofstream::out | std::ofstream::app);
        setLastEntry();
}

Log::Log(const char * logName) :
    Base("Log"),
    mLogName(logName),
    mLevel(DEFAULT_LOG_LEVEL),
    mMaxSize(DEFAULT_LOG_SIZE),
    mEntries(0) {
        // mOut.open(mLogName,std::ofstream::out | std::ofstream::app);
        setLastEntry();
}

Log::~Log() {}

void Log::resetLogLevel(e_LogLelvel_t level) {
    mLevel = level;
}

void Log::resetLogSize(int maxLogSize) {
    mMaxSize = maxLogSize;
}

//enumeration types (both scoped and unscoped) can have overloaded operators
std::ostream & operator<<(std::ostream & os, Log::e_LogLelvel_t ll) {
    switch(ll) {
        case Log::LEVEL_INFO    : os << "INFO";        break;
        case Log::LEVEL_WARN    : os << "WARNING";     break;
        case Log::LEVEL_ERROR   : os << "ERROR";       break;
        case Log::LEVEL_CRIT    : os << "CRITICAL";    break;
        case Log::LEVEL_UNKNOWN : os << "UNKNOWN";     break;
        default                 : os.setstate(std::ios_base::failbit);
    }
    return os;
}

std::ostream & operator<<(std::ostream & os, Log & log) {
    os << log.getClassName() << " [file " << log.mLogName << " / ";
    os << "level " << log.mLevel << " / ";
    os << "Max size " << ((log.mMaxSize == -1) ? "UNLIMITED" : std::to_string(log.mMaxSize));
    os << "]" << std::endl;
    return os;
}

Log::e_LogLelvel_t Log::logLevelFromString(std::string & level) {
    if(level == "INFO")     return Log::LEVEL_INFO;
    if(level == "WARNING")  return Log::LEVEL_WARN;
    if(level == "ERROR")    return Log::LEVEL_ERROR;
    if(level == "CRITICAL") return Log::LEVEL_CRIT;
    if(level == "UNKNOWN")  return Log::LEVEL_UNKNOWN;

    return Log::LEVEL_UNKNOWN;
}

void Log::setLastEntry() {
    std::string name = getLogFileName();

    // std::cout << "Getting last entry for log " << name << std::endl;

    int size = Log::fileSize(name.c_str());

    // std::cout << "Size is " << size << Std::endl;

    if(size) {
        std::ifstream ifs;
        ifs.open(name, std::ifstream::in);

        std::string line;
        int entry = 0;
        while(getline(ifs,line)) {
            sscanf(line.c_str(), "Entry %d", &entry);
        }

        std::cout << "Log " << name << ": Last entry is " << entry << std::endl;

        mEntries = entry;
    }
}

std::streampos Log::fileSize( const char* filePath ) {

    std::streampos fsize = 0;
    std::ifstream file( filePath, std::ios::binary );

    fsize = file.tellg();
    file.seekg( 0, std::ios::end );
    fsize = file.tellg() - fsize;
    file.close();

    return fsize;
}


void Log::doLogStart() {
    mOut.open(getLogFileName(),std::ofstream::out | std::ofstream::app);
    mOut << "Entry " << ++mEntries << " - " << mState << " - " << mDate.now() << "[";
    mOut.flush();
}

void Log::doMoveCmd() {
    static int num = 0;
    std::string cmd = "mv " + getLogFileName() + " " + getNewLogName(++num);
    system(cmd.c_str());
}

std::string Log::getLogFileName() {
    return mLogName + ".log";
}

std::string Log::getNewLogName(int idx) {
    return mLogName + "-" + std::to_string(idx) + ".log";
}

std::ostream & Log::getLog(e_LogLelvel_t level) {
    lock();

    mState = level;

    // std::cout << "Log file size " << size << " / max file size " << mMaxSize << std::endl;
    if(mLevel <= level && (mMaxSize == -1 || mSize < (unsigned int) mMaxSize)) {
        doLogStart();
        return mOut;
    }
    else if(mMaxSize != -1 && mSize >= (unsigned int) mMaxSize) {
        doMoveCmd();
        doLogStart();
        return mOut;
    }

    // std::cout << "Max size " << mMaxSize << " size " << mSize << std::endl;

    std::cout << "Entry " << ++mEntries << " - " << level << " - " << mDate.now() << "[";
    return std::cout;
}

const char * Log::endLog() {
    if(mLevel <= mState && (mMaxSize == -1 || mSize < (unsigned int) mMaxSize)) {
        mOut << "]\n";
        mOut.flush();
        mOut.close();
    }
    else {
        std::cout << "]" << std::endl;
    }

    // Measure new sized after not before so we can stop logging or copy if max size reached
    std::string name = getLogFileName();
    mSize = Log::fileSize(name.c_str());


    unlock();

    return "";
}


static Log::LoggerFactory fact;

Log::LoggerFactory::LoggerFactory() : 
    Base("LoggerFactory"){}

Log::LoggerFactory::~LoggerFactory() {
    fact.mLoggerMap.clear();
}

void Log::LoggerFactory::setBaseDir(const char * dir) {
    fact.mBaseDir = dir;
}

std::shared_ptr<Log> Log::LoggerFactory::initialise(const char * logName, Log::e_LogLelvel_t level, int maxLogSize) {
    std::string realLogName = fact.mBaseDir + "/" + logName; 

    auto it = fact.mLoggerMap.find(logName);
    std::shared_ptr<Log> logger = NULL;
    if(it != fact.mLoggerMap.end()) {
        logger = it->second;
    }
    else {
        logger = std::make_shared<Log>(realLogName.c_str(), level, maxLogSize);
        if(logger == NULL) {
            std::cerr << "ERROR: Memory allocation failure.." << std::endl; 
        }

        fact.mLoggerMap.insert(std::pair<std::string,std::shared_ptr<Log>>(logName,logger));
    }

    return logger;
}


std::shared_ptr<Log> Log::LoggerFactory::getLogger(const char * logName) {
    auto it = fact.mLoggerMap.find(logName);

    std::shared_ptr<Log> logger = NULL;
    if(it != fact.mLoggerMap.end()) {
        logger = it->second;
    }
    else {
        // Create default logger..
        logger = std::make_shared<Log>();
        if(logger == NULL) {
            std::cerr << "ERROR: Memory allocation failure.." << std::endl; 
        }
        else {
            fact.mLoggerMap.insert(std::pair<std::string,std::shared_ptr<Log>>(logName,logger));
        }
    }

    return logger;
}

