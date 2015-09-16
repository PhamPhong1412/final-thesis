#include "Utility.h"

std::vector<std::string> Utility::stringSplit(std::string string, std::string  delim){
	char str[1024];
	std::vector<std::string> result;
	std::strcpy(str, string.c_str());
		
	char * pch;
	const char* tmp = delim.c_str();
	pch = strtok(str, tmp);
	while (pch != NULL)
	{
		result.push_back(pch);
		pch = strtok(NULL, tmp);
	}
	return result;
}