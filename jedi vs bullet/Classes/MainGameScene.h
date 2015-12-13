#ifndef _MAIN_GAME_SCENE_H_
#define _MAIN_GAME_SCENE_H_

#include "cocos2d.h"

#include "RealGamePlayLayer.h"
#include "WidthHeightChooseHUD.h"

USING_NS_CC;

class MainGameScene : public Layer, public WidthHeightChooseDelegate
{
private:
	bool isTestMap;
	bool isPause;
public:

	static cocos2d::Scene* createScene();

	virtual bool init();

	void initWithRealGame(std::string mapText);

	void menuPlayCallback(cocos2d::Ref* pSender);
	virtual void exitBack();
    void update(float delta);
	CREATE_FUNC(MainGameScene);
};

#endif