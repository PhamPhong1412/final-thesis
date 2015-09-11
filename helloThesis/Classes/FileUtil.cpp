#include "FileUtil.h"

void FileUtil::write(std::string fileName, Vector<std::string> lines){
	std::string wpath = FileUtils::sharedFileUtils()->getWritablePath() + fileName;
	std::string directory;
	const size_t last_slash_idx = wpath.rfind('/');
	if (std::string::npos != last_slash_idx)
	{
		directory = wpath.substr(0, last_slash_idx);
	}

	if (FileUtils::getInstance()->isFileExist(wpath))
		return;

	if (!FileUtils::getInstance()->isDirectoryExist(directory))
	{
		FileUtils::getInstance()->createDirectory(directory);
	}

	FILE *fp = fopen(wpath.c_str(), "w+");
	for (std::string line : lines){
		const char* conv_my_str = line.c_str();
		fputs(conv_my_str, fp);
	}

	fclose(fp);
}

Vector<std::string> FileUtil::read(std::string fileName){
	std::string path = CCFileUtils::sharedFileUtils()->fullPathForFilename(fileName);

	ssize_t *size = new ssize_t();
	char* pBuffer = (char*)CCFileUtils::sharedFileUtils()->getFileData(path.c_str(), "rt", size);

	std::stringstream ss(pBuffer);
	std::string item;
	Vector<std::string> lines;
	while (std::getline(ss, item, '\n')) {

		lines.pushBack(item);
	}

	return lines;
}
