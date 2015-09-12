//#include "Translator.h"
//Translator* Translator::instance = NULL;
//
//Translator::Translator(){
//	std::string fileName;
//	String lang = DBContext::get(DEFAULT_LANGUAGE);
//	
//	if (lang.length() == 0)
//		fileName = "en.txt";
//	else 
//	if (lang.getCString() == "vn")
//		fileName = "vn.txt";
//	else
//	if (lang.getCString() == "jp")
//		fileName = "jp.txt";
//
//	Vector<String> linePart;
//	//for (std::string lines : FileUtil::read(fileName)){
//		//linePart = Utility::stringSplit(fileName, "t");
//		//this->data[linePart.at(0)] = linePart.at(1);
//	//}
//
//	//this->data.at(linePart.at(0));
//}
//
//Translator::~Translator(){
//
//}
//
//Translator* Translator::inst(){
//	if (!instance){
//		instance = new Translator();
//		instance->init();
//	}
//	return instance;
//}
//
//void Translator::init(){
//
//}
