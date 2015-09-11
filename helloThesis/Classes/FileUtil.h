#ifndef __FILE_UTIL_H__
#define __FILE_UTIL_H__

#include "cocos2d.h"

USING_NS_CC;

class FileUtil
{
private:
public:
	static void write(std::string fileName, Vector<std::string> lines);
	static Vector<std::string> read(std::string fileName);
};

#endif