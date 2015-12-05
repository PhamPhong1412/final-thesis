#ifndef _UTILITY_H_
#define _UTILITY_H_

#include <vector>
using namespace std;

typedef struct HttpRequestParameter
{
	std::string name;
	std::string data;
	HttpRequestParameter(std::string n, std::string d)
		:name(n),
		data(d){}
};

class Utility
{
private:

public:
	static char* stringToChar(std::string);
	static std::vector<std::string> splitString(std::string string, std::string delim);
	static bool isNumber(const std::string& s);
	static char * strcpy(char *dst, const char *src);
	static std::string getPhoneID();

	static char* buildJson(std::vector<HttpRequestParameter> values);
};

#endif