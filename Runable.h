/**
 * @file Runable.h
 * @author Barry Robinson (barry.robinson@alertlogic.com)
 * @brief 
 * @version 1.0
 * @date 28-11-2021
 * 
 * @copyright Copyright (c) Alert Logic 2021
 * 
 */
#ifndef __RUNABLE_CLASS__
#define __RUNABLE_CLASS__

class Runable {
    public:
        virtual void run() = 0;
        virtual void start() = 0;

};

#endif//__RUNABLE_CLASS__

