#ifndef __GAME_BACKGROUND_LAYER_H__
#define __BRIGDE_LAYER_H__

#include "cocos2d.h"
USING_NS_CC;

class GameBackgroundLayer : public Layer
{
private: 
	cocos2d::Sprite* background;
public:

	static cocos2d::Scene* createScene();
	virtual bool init(std::string backgroundID);
	void update(float delta);
};

#endif 
