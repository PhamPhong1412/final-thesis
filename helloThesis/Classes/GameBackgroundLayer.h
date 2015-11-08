#ifndef __GAME_BACKGROUND_LAYER_H__
#define __GAME_BACKGROUND_LAYER_H__

#include "cocos2d.h"
#include "GameConfig.h"
USING_NS_CC;

class GameBackgroundLayer : public Layer
{
private: 
public:

	//bool init(std::string backgroundID, std::vector<std::string*>* backgroundObject);
	bool init();
	void update(float delta);
};

#endif 
