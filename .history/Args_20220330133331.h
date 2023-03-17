#ifndef __ARGS__
#define __ARGS__

#include <map>
#include <string>

class Args {
public:
    Args(int argc, const char ** argv);
    std::string getValue(std::string key);
    bool isFlagPressent(std::string key);

private:

    std::map<std::string,std::string>mArgs;
};

#endif//__ARGS__