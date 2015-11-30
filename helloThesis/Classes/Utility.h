#ifndef _UTILITY_H_
#define _UTILITY_H_

#include <vector>
#include "spine/Json.h"
using namespace std;

class Utility
{
private:

public:
	static std::vector<std::string> splitString(std::string stringToSplit, std::string delim);
	static bool isNumber(const std::string& s);

	static Json* buildJson(std::vector<string>* content);
	static char* stringToChar(std::string);


};

#endif