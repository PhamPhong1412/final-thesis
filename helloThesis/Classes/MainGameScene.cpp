#include "MainGameScene.h"


Scene* MainGameScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = MainGameScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool MainGameScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	//TTFConfig config_font96("Marker Felt.ttf", 96);
	//Label* startGame = Label::createWithTTF(config_font96, "Start game!");
	//startGame->setPosition(Vec2(1,1));
	//this->addChild(startGame);

	MenuItemFont* quit = MenuItemFont::create("éo chơi nữa", CC_CALLBACK_1(MainGameScene::menuPlayCallback, this));
	quit->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 5 + visibleSize.height / 2));

	Menu *mainMenu = Menu::create(quit, nullptr);
	mainMenu->setPosition(Vec2(0, 0));
	this->addChild(mainMenu);

	return true;
}


void MainGameScene::menuPlayCallback(cocos2d::Ref* pSender){

}
