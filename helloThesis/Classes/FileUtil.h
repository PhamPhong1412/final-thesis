#ifndef __FILE_UTIL_H__
#define __FILE_UTIL_H__

#include "cocos2d.h"

USING_NS_CC;

class FileUtil
{
private:
public:
	static void write(std::string fileName, std::vector<std::string> lines);
	static std::vector<std::string> read(std::string fileName);
};

#endif