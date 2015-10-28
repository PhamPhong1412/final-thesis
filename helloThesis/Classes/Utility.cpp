#include "Utility.h"

std::vector<std::string> Utility::splitString(std::string string, std::string  delim){
	char str[1002004];
	char * pch;
	const char* tmp = delim.c_str();
	std::vector<std::string> result;
	std::strcpy(str, string.c_str());
		
	pch = strtok(str, tmp);
	while (pch != NULL)
	{
		result.push_back(pch);
		pch = strtok(NULL, tmp);
	}
	return result;
}