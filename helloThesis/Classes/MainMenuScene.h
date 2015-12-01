#ifndef _MAIN_MENU_SCENE_H_
#define _MAIN_MENU_SCENE_H_


#include "cocos2d.h"
#include "cocos-ext.h"
#include "MainGameScene.h"
#include "ShopScene.h"
#include "MapMakingScene.h"
#include "Utility.h"
#include "ui/CocosGUI.h"
#include "Translator.h"
#include "LoginScene.h"
#include "RatingTableCell.h"
#include "HttpServices.h"
#include "RankingScene.h"

USING_NS_CC;

using namespace cocos2d::ui;

class MainMenuScene : public Layer, public HttpServicesDelegate

{
private:

public:
    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;
    
    virtual bool init();

	virtual void getUID(std::string uid);

	static cocos2d::Scene* createScene();
    
	void transitionToGameScene();
	void toGameScene();
    
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