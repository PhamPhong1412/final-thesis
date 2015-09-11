#ifndef _UTILITY_H_
#define _UTILITY_H_

#include "cocos2d.h"

USING_NS_CC;

class Utility
{
private:

public:
	static Vector<String> stringSplit(std::string string, const char* delim);
};

#endif