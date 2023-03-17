// ==================================================================
// Lockable.h
//
// NOTE: 
// ==================================================================
#ifndef __LOCKABLE_CLASS__
#define __LOCKABLE_CLASS__

// #include "../Base.h"

// #include <pthread.h>

class Lockable {
    public:
        virtual void lock()   = 0;
        virtual void unlock() = 0;

    private:
};

#endif//__LOCKABLE_CLASS__

