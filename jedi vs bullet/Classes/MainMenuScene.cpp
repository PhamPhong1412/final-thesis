#include "MainMenuScene.h"


Scene* MainMenuScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = MainMenuScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool MainMenuScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	std::string s = "abdf \t fwef";
	Utility::splitString(s, "\t");

    initButton();
	return true;
}

void MainMenuScene::initButton()
{
    auto mBackGround = Sprite::create("bg3.png");
    mBackGround->setScale(visibleSize.height/mBackGround->getContentSize().height);
    mBackGround->setAnchorPoint(Vec2(0.5,0.5));
    mBackGround->setPosition((origin.x +visibleSize.width)/2, (origin.y +visibleSize.height)/2);
    addChild(mBackGround);
    
    auto mNameSprite = Sprite::create("GameName.png");
    mNameSprite->setScale((visibleSize.width/2)/mNameSprite->getContentSize().width);
    mNameSprite->setAnchorPoint(Vec2(0.5,1));
    mNameSprite->setPosition(Vec2((origin.x +visibleSize.width)/2,origin.y + visibleSize.height - 50));
    addChild(mNameSprite);
    
    auto mRaceButton = MenuItemImage::create("RaceNormal.png","RaceSelected.png",CC_CALLBACK_1(MainMenuScene::menuPlayCallback,this));

    mRaceButton->setAnchorPoint(Vec2(0.5,0.5));
    mRaceButton->setScale((visibleSize.width/5)/mRaceButton->getNormalImage()->getContentSize().width);
    Vec2 tRaceButtonPos = Vec2((origin.x +visibleSize.width)/2,(origin.y + visibleSize.height)/2 + mRaceButton->getNormalImage()->getContentSize().height/3);
    mRaceButton->setPosition(tRaceButtonPos);
    
    
    
    
    
    cocos2d::Vector<MenuItem*> items;
    items.pushBack(mRaceButton);
    
    auto menu = Menu::createWithArray(items);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    
    
}

void MainMenuScene::menuPlayCallback(cocos2d::Ref *pSender)
{
	auto gameScene = MainGameScene::createScene();
	Director::getInstance()->replaceScene(gameScene);
}


void MainMenuScene::menuSettingCallback(cocos2d::Ref *pSender)
{
    CCLOG("Setting");
}

void MainMenuScene::menuExitCallback(cocos2d::Ref* pSender){
	Director::getInstance()->end();
}
