#ifndef _UTILITY_H_
#define _UTILITY_H_

#include <vector>
using namespace std;

class Utility
{
private:

public:
	static std::vector<std::string> splitString(std::string string, std::string delim);
	static bool isNumber(const std::string& s);
};

#endif