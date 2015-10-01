#ifndef _GAME_PLAY_LAYER_H__
#define _GAME_PLAY_LAYER_H__

#include "cocos2d.h"
#include "b2Layer.h"
#include "Runner.h"
USING_NS_CC;

class GamePlayLayer : public b2Layer
{
private: 

public:

	virtual bool init();
	void update(float delta);

	CREATE_FUNC(GamePlayLayer);
	CC_SYNTHESIZE(Runner*, mRunner, Runner);
};

#endif 
