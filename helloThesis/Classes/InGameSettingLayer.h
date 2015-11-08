#ifndef _IN_GAME_SETTING_LAYER
#define _IN_GAME_SETTING_LAYER

#include "HUDLayer.h"
USING_NS_CC;

class InGameSettingLayer : public HUDLayer
{
private:
	void menuBackCallback();
	bool init();
public:
	InGameSettingLayer(Layer* parent);
	~InGameSettingLayer();



	//void onTouchesMoved(const std::vector<Touch*>& touches, Event  *event);
	//void onTouchesEnded(const std::vector<Touch*>& touches, Event  *event);
	//void onTouchesCancelled(const std::vector<Touch*>& touches, cocos2d::Event  *event);


	//CC_SYNTHESIZE(Runner*, mRunner, Runner);
};

#endif 
