#ifndef _GAME_HUD_LAYER_H__
#define _GAME_HUD_LAYER_H__
#include "cocos2d.h"
#include "GameConfig.h"
#include "Utility.h"
#include "HUDLayer.h"
USING_NS_CC;
class GameHUDLayer;

class GameHUDLayerDelegate
{
public:
	/**
	* @js NA
	* @lua NA
	*/
	virtual ~GameHUDLayerDelegate() {}
	/**
	* @js NA
	* @lua NA
	*/
	virtual void exitBack() {};
	virtual void saveMap() {};
};
class GameHUDLayer : public HUDLayer
{
private:
	GameHUDLayerDelegate *mDelegate;
	void menuNextCallback();
	void menuBackCallback();
	bool init(float x, float y, float time);
public:
	GameHUDLayer(Layer* parent, float time);
	~GameHUDLayer();
	void setDelegate(GameHUDLayerDelegate* pDelegate) { mDelegate = pDelegate; }
	//touches event
	//void onTouchesBegan(const std::vector<Touch*>& touches, Event  *event);
	//void onTouchesMoved(const std::vector<Touch*>& touches, Event  *event);
	//void onTouchesEnded(const std::vector<Touch*>& touches, Event  *event);
	//void onTouchesCancelled(const std::vector<Touch*>& touches, cocos2d::Event  *event);

	//CC_SYNTHESIZE(Runner*, mRunner, Runner);
};

#endif 
