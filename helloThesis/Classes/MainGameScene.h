#ifndef _MAIN_GAME_SCENE_H_
#define _MAIN_GAME_SCENE_H_

#include "cocos2d.h"
#include "GameBackgroundLayer.h"
#include "TestGamePlayLayer.h"
#include "RealGamePlayLayer.h"
#include "MapMakingScene.h"
#include "GameMap.h"
#include "DBContext.h"
#include "HUDLayer.h"
#include "GameHUDLayer.h"
#include "InGameSettingLayer.h"

USING_NS_CC;

class MainGameScene : public Layer, public TestGamePlayLayerDelegate, public RealGamePlayLayerDelegate
{
private:
	bool isPause;
    Label *mTimeLabel;
	
public:

	static cocos2d::Scene* createScene(bool isTestMap, std::string mapText, HttpShortMapInfo mapInfo);

	virtual bool init();

	void initWithTestGame(std::string mapText,Layer *ParentLayer);
	void initWithRealGame(std::string mapText, Layer *ParentLayer, HttpShortMapInfo mapInfo);
	
	void menuPlayCallback(cocos2d::Ref* pSender);

	void menuBackCallback(cocos2d::Ref* pSender);
	void menuSettingCallback(cocos2d::Ref* pSender);
    
    virtual void testUpdateTime(float time);
    virtual void realUpdateTime(float time);
	CREATE_FUNC(MainGameScene);
};

#endif