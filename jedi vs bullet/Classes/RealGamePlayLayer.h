#ifndef _REAL_GAME_PLAY_LAYER_H__
#define _REAL_GAME_PLAY_LAYER_H__

#include "cocos2d.h"
#include "Anakin.h"
#include "GameConfig.h"
USING_NS_CC;

class RealGamePlayLayer : public Layer
{
private:

public:
	virtual bool init(std::string map);
	void update(float delta);

	//touches event
	bool onTouchBegan(Touch *touch, Event *event);
	void onTouchMoved(Touch *touch, Event *event);
	void onTouchEnded(Touch *touch, Event *event);
	void onTouchCancelled(Touch *touch, Event *event);

	Anakin* mAnakin;

};

#endif 
