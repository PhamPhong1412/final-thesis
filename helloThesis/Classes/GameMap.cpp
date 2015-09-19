#include "GameMap.h"
GameMap::GameMap(){
}

GameMap::~GameMap(){

}

void GameMap::load(std::string mapID){
	if (mapID == "test"){
		this->backgroundName = "bg_1";
		this->background = new std::vector<string*>();
	}
}

