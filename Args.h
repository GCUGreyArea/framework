#ifndef __ARGS__
#define __ARGS__

#include <map>

#include "Base.h"

class Args : public Base {
    public:
        Args(int argc, const char ** argv);  
        void addStringValue(const char * idxName, const char * altName, const char * def);
        void addNaturalValue(const char * idxName, const char * altName, int def);

        int getNaturalValue(const char * key);
        const char * getStringValue(const char * key);

        bool isValuePresent(const char * key, const char * defval);

    private:
    const char ** mArgv;
    int mArgc;

    std::map<std::string,int> mIntArgs;
    std::map<std::string,std::string>mStrArgs;
};

#endif//__ARGS__