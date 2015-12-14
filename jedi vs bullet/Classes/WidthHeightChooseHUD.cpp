//
//  WidthHeightChooseHUD.cpp
//  GameRun
//
//  Created by Thien Banh on 11/14/15.
//
//

#include "WidthHeightChooseHUD.h"
#include "MainMenuScene.h"

WidthHeightChooseHUD::WidthHeightChooseHUD(Layer* parent, bool canExit) : HUDLayer(parent, canExit){
	this->init();
}

WidthHeightChooseHUD::~WidthHeightChooseHUD(){

}

// on "init" you need to initialize your instance
bool WidthHeightChooseHUD::init()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	//auto boxSprite = Sprite::create("Windown1.png");
	//boxSprite->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	//boxSprite->setScale((DESIGN_SCREEN_WIDTH / 1.5) / boxSprite->getContentSize().width, (DESIGN_SCREEN_HEIGHT / 1.5) / boxSprite->getContentSize().height);
	//this->addChild(boxSprite);

	cocos2d::Vector<MenuItem*> items;

	auto mBackButton = MenuItemImage::create("ExitNormal.png", "ExitSelected.png", CC_CALLBACK_0(WidthHeightChooseHUD::menuBackCallback, this));
	mBackButton->setAnchorPoint(Vec2(0.5, 0));
	mBackButton->setScale(70 / mBackButton->getContentSize().width);
	mBackButton->setPosition(Vec2(DESIGN_SCREEN_WIDTH / 3, 0));
	items.pushBack(mBackButton);

	auto mNextButton = MenuItemImage::create("AddNormal.png", "AddSelected.png", CC_CALLBACK_0(WidthHeightChooseHUD::menuShareCallback, this));
	mNextButton->setAnchorPoint(Vec2(0.5, 0));
	mNextButton->setScale(70 / mNextButton->getContentSize().width);
	mNextButton->setPosition(Vec2((DESIGN_SCREEN_WIDTH * 2) / 3, 0));
	items.pushBack(mNextButton);

	auto menu = Menu::createWithArray(items);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	return true;
}
void WidthHeightChooseHUD::menuShareCallback()
{
	mDelegate->exitBack();
	exit();

}
void WidthHeightChooseHUD::menuBackCallback()
{
	//auto mainScene = MainMenuScene::createScene();
	//Director::getInstance()->replaceScene(mainScene);
}
