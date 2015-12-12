#ifndef _MAIN_MENU_SCENE_H_
#define _MAIN_MENU_SCENE_H_


#include "cocos2d.h"
#include "cocos-ext.h"
#include "MainGameScene.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace cocos2d::ui;

class MainMenuScene : public Layer

{
private:

public:
    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;
	MenuItemImage *mSoundButton;
    virtual bool init();


	static cocos2d::Scene* createScene();
   
    void initButton();
	void menuSoundCallback(cocos2d::Ref* pSender);
	void menuRateCallback(cocos2d::Ref* pSender);
	void menuPlayCallback(cocos2d::Ref* pSender);
	void menuSettingCallback(cocos2d::Ref* pSender);
	void menuExitCallback(cocos2d::Ref* pSender);

    
	CREATE_FUNC(MainMenuScene);

};

#endif