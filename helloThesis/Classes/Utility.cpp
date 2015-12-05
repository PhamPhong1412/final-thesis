#include "Utility.h"

std::vector<string> Utility::splitString(std::string string, std::string  delim){

	char* str = stringToChar(string);

	char * pch;
	const char* tmp = delim.c_str();
	std::vector<std::string> result;
	//strcpy(str, string.c_str());
	//std::strcpy(str, string.c_str());
		
	pch = strtok(str, tmp);
	while (pch != NULL)
	{
		result.push_back(pch);
		pch = strtok(NULL, tmp);
	}
	return result;
}

char* Utility::stringToChar(std::string str){
	if (str.length() < 1000)
		return  strcpy(new char[1000], str.c_str());
	else
	if (str.length() < 10000)
		return  strcpy(new char[10000], str.c_str());
	else
	if (str.length() < 100000)
		return  strcpy(new char[100000], str.c_str());
	else
		return  strcpy(new char[1000000], str.c_str());
}

char * Utility::strcpy(char *dst, const char *src)   //[1]
{
	//assert(dst != NULL && src != NULL);    //[2]

	char *ret = dst;  //[3]

	while ((*dst++ = *src++) != '\0'); //[4]

	return ret;
}

bool Utility::isNumber(const std::string& s){
	if (s.size() == 0)
	{
		return false;
	}
	return(strspn(s.c_str(), "-.0123456789") == s.size());
}


std::string Utility::getPhoneID(){
	return "test";
}


char* Utility::buildJson(std::vector<HttpRequestParameter> values){
	string result="{";
	for (int i = 0; i < values.size(); i++){
		result += "\"" + values[i].name + "\"";
		result += ":";
		result += "\"" + values[i].data + "\"";
		if (i != values.size() - 1)
			result += ",";
	}
	result += "}";
	return stringToChar(result);
}