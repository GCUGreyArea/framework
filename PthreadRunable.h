// ==================================================================
// pthreadRunable.h
//
// NOTE: 
// ==================================================================
#ifndef __PTHREADRUNABLE_CLASS__
#define __PTHREADRUNABLE_CLASS__

#include <pthread.h>

#include "Runable.h"

class PthreadRunable : public Runable {
    public:
        PthreadRunable(const char * threadName);
        virtual void start();
        void join();
        bool running() {return mRunning;}

    protected:
        static void * runThread(void * me);
        std::string & getThreadName() {return mThreadName;}

    private:
        std::string mThreadName;
        pthread_t mThread;
        int mRunState;
        bool mRunning;
        void * mReturn;
};

#endif//__PTHREADRUNABLE_CLASS__

