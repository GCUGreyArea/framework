// ==================================================================
// PthreadRunable.cpp
//
// NOTE: 
// ==================================================================

#include <iostream>
#include <string>

// Support libraries gts kernel development
// #include <support.h>

#include "PthreadRunable.h"

PthreadRunable::PthreadRunable(const char * threadName) : 
    mThreadName(threadName),
    mThread(0),
    mRunState(-1),
    mRunning(false),
    mReturn(nullptr) {}

void * PthreadRunable::runThread(void * m) {
    PthreadRunable * me = (PthreadRunable*) m;
    
    if(me) {
        me->mRunning = true;
        me->run();
        me->mRunning = false;
    }

    return me;
}

void PthreadRunable::start() {
    mRunState = pthread_create(&mThread,NULL,PthreadRunable::runThread,this);
}

void PthreadRunable::join() {
    pthread_join(mThread, &mReturn);
}