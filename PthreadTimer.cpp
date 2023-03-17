// ==================================================================
// PthreadTimer.cpp
//
// NOTE: 
// ==================================================================

#include <iostream>
#include <string>

#include <unistd.h>

// Support libraries gts kernel development
// #include <support.h>

#include "PthreadTimer.h"

PthreadTimer::PthreadTimer(const char * timerName,int timeout) : 
    PthreadRunable(timerName),
    mTimeout(timeout),
    mRunTimer(false) {}

void PthreadTimer::run() {
    while(mRunTimer) {
        timeout();

        usleep(mTimeout);
    }
}


void PthreadTimer::start() {
    mRunTimer = true;
    PthreadRunable::start();
}