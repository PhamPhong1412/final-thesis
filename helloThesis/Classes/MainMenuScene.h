#ifndef _MAIN_MENU_SCENE_H_
#define _MAIN_MENU_SCENE_H_


#include "cocos2d.h"
#include "MainGameScene.h"
#include "MapMakingScene.h"
#include "Utility.h"
#include "ui/CocosGUI.h"
#include "Translator.h"
#include "LoginScene.h"

USING_NS_CC;
using namespace cocos2d::ui;

class MainMenuScene : public Layer
{
private:

public:
    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;
	static cocos2d::Scene* createScene();

	virtual bool init();
    
    void initButton();
    
	void menuPlayCallback(cocos2d::Ref* pSender);
	void menuMakeMapCallback(cocos2d::Ref* pSender);
	void menuSettingCallback(cocos2d::Ref* pSender);
    void menuShopCallback(cocos2d::Ref* pSender);
    void menuRatingCallback(cocos2d::Ref* pSender);
	void menuExitCallback(cocos2d::Ref* pSender);

	CREATE_FUNC(MainMenuScene);
};

#endif