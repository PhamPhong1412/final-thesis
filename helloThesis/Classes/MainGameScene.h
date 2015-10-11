#ifndef _MAIN_GAME_SCENE_H_
#define _MAIN_GAME_SCENE_H_

#include "cocos2d.h"
#include "GameBackgroundLayer.h"
#include "GamePlayLayer.h"
#include "GameMap.h"
#include "DBContext.h"
USING_NS_CC;

class MainGameScene : public Layer
{
private:
	GameMap* gameMap;
public:

	static cocos2d::Scene* createScene();

	virtual bool init();

	void menuPlayCallback(cocos2d::Ref* pSender);

	CREATE_FUNC(MainGameScene);
};

#endif