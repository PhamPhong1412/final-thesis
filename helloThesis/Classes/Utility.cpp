#include "Utility.h"

std::vector<string> Utility::splitString(std::string stringToSplit, std::string  delim){

	char* str = Utility::stringToChar(stringToSplit);
	char * pch;
	const char* tmp = delim.c_str();
	std::vector<std::string> result;
	std::strcpy(str, stringToSplit.c_str());
		
	//pch = strtok(stringToSplit.c_str(), tmp);
	pch = strtok(str, tmp);
	while (pch != NULL)
	{
		result.push_back(pch);
		pch = strtok(NULL, tmp);
	}
	delete str;
	delete pch;
	return result;
}

char* Utility::stringToChar(std::string string){
	char* str;
	if (string.length()<1000)
		str = new char[1000];
	else
	if (string.length()<10000)
		str = new char[10000];
	else
	if (string.length()<100000)
		str = new char[100000];
	else
		str = new char[1002004];
	return str;
}

bool Utility::isNumber(const std::string& s){
	if (s.size() == 0)
	{
		return false;
	}
	return(strspn(s.c_str(), "-.0123456789") == s.size());
}


Json* Utility::buildJson(std::vector<string>* content){
	if (content->size() % 2 != 0)
		return Json_create((""));
	string stringContent ;
	stringContent += '{';
	for (int i = 0; i < content->size(); i += 2){
		stringContent += "\"" + content->at(i) + "\":\"" + content->at(i+1)+"\"";
		if (i == content->size() - 1){
			stringContent += ";";
		}
		else{
			stringContent += "}";
		}
	}
	return Json_create(stringContent.c_str());
}