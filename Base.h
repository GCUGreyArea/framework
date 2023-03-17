#ifndef __BASE__
#define __BASE__

#include <string>
#include <iostream>

class Base {
    public:

        Base(const char * name) : mClassName(name) {}

        std::string getClassName() {return mClassName;};

    private:
        Base() {
            std::cout << "class has no name - use proper constructor.." << std::endl;
            abort();
        }

        const std::string mClassName;
};

#endif//__BASE__