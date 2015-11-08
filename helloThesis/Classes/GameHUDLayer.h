#ifndef _GAME_HUD_LAYER_H__
#define _GAME_HUD_LAYER_H__
#include "cocos2d.h"
#include "GameConfig.h"
#include "Utility.h"
USING_NS_CC;

class GameHUDLayer : public Layer
{
private:

public:

	virtual bool init();

	//touches event
	//void onTouchesBegan(const std::vector<Touch*>& touches, Event  *event);
	//void onTouchesMoved(const std::vector<Touch*>& touches, Event  *event);
	//void onTouchesEnded(const std::vector<Touch*>& touches, Event  *event);
	//void onTouchesCancelled(const std::vector<Touch*>& touches, cocos2d::Event  *event);


	//CC_SYNTHESIZE(Runner*, mRunner, Runner);
	CREATE_FUNC(GameHUDLayer);
};

#endif 
