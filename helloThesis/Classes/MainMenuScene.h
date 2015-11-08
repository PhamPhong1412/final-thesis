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
#include "HelloWorldScene.h"
#include "ABCXYZ.h"
USING_NS_CC;
USING_NS_CC_EXT;

using namespace cocos2d::ui;

class MainMenuScene : public Layer,public cocos2d::extension::TableViewDelegate,cocos2d::extension::TableViewDataSource

{
private:

public:
    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;
    
    virtual bool init();
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


    
    virtual TableViewCell* tableCellAtIndex(TableView *table, ssize_t idx);
    virtual ssize_t numberOfCellsInTableView(TableView *table);
    virtual cocos2d::Size tableCellSizeForIndex(TableView *table, ssize_t idx) override;
    virtual void tableCellTouched(TableView *table, TableViewCell *cell);
    
    virtual void scrollViewDidScroll(cocos2d::extension::ScrollView *view) {};
    
//    virtual void scrollViewDidZoom(ScrollView *view) {};
    
	CREATE_FUNC(MainMenuScene);

};

#endif