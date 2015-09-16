#include "Translator.h"
Translator* Translator::instance = NULL;

Translator::Translator(){
	std::string fileName;
	std::string lang = DBContext::get(DEFAULT_LANGUAGE);
	
	if (lang.length() == 0){
		DBContext::set(DEFAULT_LANGUAGE, "vn");
		fileName = "vn.txt";
	}else
	if (lang == "en")
		fileName = "en.txt";
	else
	if (lang == "vn")
		fileName = "vn.txt";
	else
	if (lang == "jp")
		fileName = "jp.txt";

	std::vector<std::string> linePart;
	for (std::string line : FileUtil::read(fileName)){
		linePart = Utility::stringSplit(line, "::");
		this->data[linePart.at(0)] = linePart.at(1);
	}
}

Translator::~Translator(){

}

Translator* Translator::inst(){
	if (!instance){
		instance = new Translator();
		instance->init();
	}
	return instance;
}

void Translator::init(){

}

std::string Translator::translate(std::string message){
	return this->data.at(message);
}
