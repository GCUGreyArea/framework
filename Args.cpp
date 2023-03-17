#include <iostream>
#include <string>

#include <map>

#include "Args.h"

Args::Args(int argc, const char ** argv) : 
    Base("Args"),
    mArgv(argv), 
    mArgc(argc) 
{}


void Args::addStringValue(const char * key, const char * alt, const char * def) {

	std::string value = "";
	int idx = 0;
    
    std::string k = key;
    std::string a = alt;


	while(idx<mArgc) {
		// Input file
		if(mArgv[idx] == k || mArgv[idx] == a) {
			if(++idx<mArgc) {
				value = mArgv[idx];
                // std::cout << "Found value [key " << key << " val " << value << "]" << std::endl;
				break;
			}			
		}

		idx++;
	}

    if(value == "") {
        value = def;
    }

    mStrArgs.insert(std::make_pair(key, value));

}

void Args::addNaturalValue(const char * key, const char * alt, int def) {

	int value = -1;
	int idx = 0;
    
    std::string k = key;
    std::string a = alt;


	while(idx<mArgc) {
		// Input file
		if(mArgv[idx] == k || mArgv[idx] == a) {
			if(++idx<mArgc) {
				value = atoi(mArgv[idx]);
				break;
			}			
		}

		idx++;
	}

    if(value == -1) {
        value = def;
    }

    mIntArgs.insert(std::make_pair(key, value));
}

int Args::getNaturalValue(const char * key) {
    std::map<std::string,int>::iterator it = mIntArgs.find(key);

    if(it != mIntArgs.end()) {
        return it->second;
    }

    return -1;
}


const char * Args::getStringValue(const char * key) {
    std::map<std::string,std::string>::iterator it = mStrArgs.find(key);

    if(it != mStrArgs.end()) {
        return it->second.c_str();
    }

    return NULL;
}

bool Args::isValuePresent(const char * key, const char * defval) {
    std::string str = getStringValue(key);
    if(str != defval) {
        return true;
    }

    return false;
}
