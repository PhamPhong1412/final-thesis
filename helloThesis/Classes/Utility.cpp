#include "Utility.h"

Vector<String> Utility::stringSplit(std::string string, const char*  delim){
	Vector<String> result;
	std::stringstream ss(string);
	std::string item;
	while (std::getline(ss, item, delim)) {
		result.pushBack(item);
	}
	return result;
}