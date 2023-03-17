/**
 * @file Log.h
 * @author Barry Robinson (barry.robinson@alertlogic.com)
 * @brief 
 * @version 1.0
 * @date 28-11-2021
 * 
 * @copyright Copyright (c) Alert Logic 2021
 * 
 */
#ifndef __LOG_CLASS__
#define __LOG_CLASS__


#include <fstream>
#include <map>
#include <memory>

#include "Base.h"
#include "PthreadLockable.h"
#include "Date.h"

/**
 * @brief 
 * @note This needs reworking with PTHreadRunnable
 */

class Log : public PthreadLockable, public Base {
public:
    typedef enum {
        LEVEL_INFO,
        LEVEL_WARN,
        LEVEL_ERROR,
        LEVEL_CRIT,
        LEVEL_UNKNOWN
    } e_LogLelvel_t;

    friend std::shared_ptr<Log> initialise(const char * logName, Log::e_LogLelvel_t level, int maxLogSize);
    virtual ~Log();

    Log();
    Log(const char * logName, e_LogLelvel_t level, int maxLogSize);
    Log(const char * logName, e_LogLelvel_t level);
    Log(const char * logName);

public:
    constexpr static int MAX_LEVEL_STR_LEN   = 6;
    constexpr static int FILE_SIZE_UNLIMITED = -1;
    constexpr static int FILE_SIZE_1k        = (1  * 1024);
    constexpr static int FILE_SIZE_5k        = (5  * 1024);
    constexpr static int FILE_SIZE_10k       = (10 * 1024);
    constexpr static int FILE_SIZE_20k       = (20 * 1024);
    constexpr static int FILE_SIZE_50k       = (50 * 1024);
    constexpr static int FILE_SIZE_256k      = (256 * 1024);      
    constexpr static int FILE_SIZE_512k      = (512 * 1024);      
    constexpr static int FILE_SIZE_1Mb       = (1024 * 1024);     
    constexpr static int FILE_SIZE_2Mb       = (2048 * 1024);     
    constexpr static int FILE_SIZE_10Mb      = (10 * 1024 * 1024);
    constexpr static int FILE_SIZE_20Mb      = (20 * 1024 * 1024);
    constexpr static int FILE_SIZE_50Mb      = (50 * 1024 * 1024);   

    // constexpr static const char * logTemplate = "Entry %d - %s - %s %s %d %02d:%02d:02d %04d [";
    static Log::e_LogLelvel_t logLevelFromString(std::string & level);
    std::ostream& getLog(e_LogLelvel_t level);
    const char * endLog(); 
    
    void resetLogLevel(e_LogLelvel_t level);
    void resetLogSize(int maxLogSize);
    // Friend functions to print out log levels to streams and print log objects
    friend std::ostream & operator<<(std::ostream & os, Log::e_LogLelvel_t ll);
    friend std::ostream & operator<<(std::ostream & os, Log & log);
    std::string getLogFileName();
    int getLogFileMaxSize() {return mMaxSize;}
    bool isLogMaxSize() {return mSize < (unsigned int) mMaxSize ? false : true;};

protected:
    std::string getNewLogName(int idx);
    void doLogStart();
    void doMoveCmd();
    static std::streampos fileSize( const char* filePath );
    void setLastEntry();

private:

    // pthread_mutex_t mMutex; // Mutex lock
    std::string mLogName;   // Name of the log file
    std::ofstream mOut;     // Output stream fro the log 
    Date mDate;             // Current date and time
    e_LogLelvel_t mLevel;   // Level to start logging at 
    e_LogLelvel_t mState;   // Last log state
    int mMaxSize;           // Maximum log size in bytes
    unsigned int mEntries;  // Current number of log entries
    unsigned int mSize;     // Current size of the log file

    // Default values
    constexpr static const int DEFAULT_LOG_SIZE = 10240;
    constexpr static const e_LogLelvel_t DEFAULT_LOG_LEVEL = Log::LEVEL_ERROR; 
    constexpr static const char * DEFAULT_LOG_FILE = "/var/log/app.log";

public:
    class LoggerFactory : public Base {
    public:
        LoggerFactory();
        ~LoggerFactory();

        static std::shared_ptr<Log> initialise(const char * logName, Log::e_LogLelvel_t level, int maxLogSize);
        static std::shared_ptr<Log> getLogger(const char * logName);
        static void setBaseDir(const char * dir);

    private:
        std::map<std::string,std::shared_ptr<Log>> mLoggerMap;
        std::string mBaseDir;

    };
};

#endif//__LOG_CLASS__

