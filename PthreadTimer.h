// ==================================================================
// PthreadTimer.h
//
// NOTE: 
// ==================================================================
#ifndef __PTHREADTIMER_CLASS__
#define __PTHREADTIMER_CLASS__


#include "PthreadRunable.h"

class PthreadTimer : public PthreadRunable {
    public:
        PthreadTimer(const char * name,int timeout);
        virtual void timeout() = 0;
        virtual void start();
        void run();

        std::string & getTimerName() {return getThreadName();}

    private:
        int mTimeout;
        bool mRunTimer;
};

#endif//__PTHREADTIMER_CLASS__

