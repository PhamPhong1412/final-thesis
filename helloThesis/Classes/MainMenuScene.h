#ifndef _MAIN_MENU_SCENE_H_
#define _MAIN_MENU_SCENE_H_


#include "cocos2d.h"
#include "MainGameScene.h"
#include "MapMakingScene.h"
#include "Utility.h"
#include "Translator.h"
#include "LoginScene.h"
USING_NS_CC;

class MainMenuScene : public Layer
{
private:

public:

	static cocos2d::Scene* createScene();

	virtual bool init();

	void menuPlayCallback(cocos2d::Ref* pSender);
	void menuMakeMapCallback(cocos2d::Ref* pSender);
	void menuSettingCallback(cocos2d::Ref* pSender);
	void menuExitCallback(cocos2d::Ref* pSender);

	CREATE_FUNC(MainMenuScene);
};

#endif