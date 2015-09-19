#ifndef __GAME_MAP_H__
#define __GAME_MAP_H__


#include "Utility.h"
using namespace std;
class GameMap
{
private:
public:
	string backgroundName;
	std::vector<string*>* obstacles;
	std::vector<string*>* background;

	GameMap();
	~GameMap();

	void load(string mapID);

	void save();
	void upload();

	void create();
	std::string translate(std::string message);
	
};

#endif