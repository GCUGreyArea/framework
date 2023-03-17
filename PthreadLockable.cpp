// ==================================================================
// PthreadLockable.cpp
//
// NOTE: 
// ==================================================================

#include <iostream>
#include <string>

// Support libraries gts kernel development
// #include <support.h>

#include "PthreadLockable.h"

PthreadLockable::PthreadLockable() {
    pthread_mutex_init(&mMutex,NULL);
}

PthreadLockable::~PthreadLockable() {
    pthread_mutex_destroy(&mMutex);
}

void PthreadLockable::lock() {
    pthread_mutex_lock(&mMutex);
}

void PthreadLockable::unlock() {
    pthread_mutex_unlock(&mMutex);
}