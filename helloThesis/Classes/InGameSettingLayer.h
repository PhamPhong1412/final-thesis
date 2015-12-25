#ifndef _IN_GAME_SETTING_LAYER
#define _IN_GAME_SETTING_LAYER

#include "HUDLayer.h"
USING_NS_CC;

class InGameSettingLayer : public HUDLayer
{
private:
    void menuHomeCallback();
	void menuReplayCallback();
	bool init();
public:
	InGameSettingLayer(Layer* parent);
	~InGameSettingLayer();

};

#endif 
