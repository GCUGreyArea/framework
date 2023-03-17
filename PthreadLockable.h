// ==================================================================
// pthreadLockable.h
//
// NOTE: 
// ==================================================================
#ifndef __PTHREADLOCKABLE_CLASS__
#define __PTHREADLOCKABLE_CLASS__

#include <pthread.h>

#include "Base.h"
#include "Lockable.h"

class PthreadLockable : public Lockable {
    public:
        PthreadLockable();
        ~PthreadLockable();

        virtual void lock();
        virtual void unlock();

    private:
        pthread_mutex_t mMutex;
};

#endif//__PTHREADLOCKABLE_CLASS__

