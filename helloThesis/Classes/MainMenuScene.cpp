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

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	std::string s = "abdf \t fwef";
	Utility::splitString(s, "\t");

	MenuItemFont* playGame = MenuItemFont::create(Translator::inst()->translate(START_GAME_BUTTON), CC_CALLBACK_1(MainMenuScene::menuPlayCallback, this));
	playGame->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 5 + visibleSize.height / 2));

	MenuItemFont* makeMap = MenuItemFont::create("Map", CC_CALLBACK_1(MainMenuScene::menuMakeMapCallback, this));
	makeMap->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 5 + visibleSize.height / 2 - visibleSize.height / 6));

	MenuItemFont* setting = MenuItemFont::create("Setting", CC_CALLBACK_1(MainMenuScene::menuSettingCallback, this));
	setting->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 5 + visibleSize.height / 2 - 2 * visibleSize.height / 6));

	MenuItemFont* quit = MenuItemFont::create("Exit", CC_CALLBACK_1(MainMenuScene::menuExitCallback, this));
	quit->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 5 + visibleSize.height / 2 - 3 * visibleSize.height / 6));

	Menu *mainMenu = Menu::create(playGame, makeMap, setting, quit, nullptr);
	mainMenu->setPosition(Vec2(0, 0));
	this->addChild(mainMenu);

	return true;
}

void MainMenuScene::menuPlayCallback(cocos2d::Ref* pSender){
	auto gameScene = MainGameScene::createScene();
	Director::getInstance()->replaceScene(gameScene);
}

void MainMenuScene::menuMakeMapCallback(cocos2d::Ref* pSender){
	auto mapMakingScene = MapMakingScene::createScene();
	Director::getInstance()->replaceScene(mapMakingScene);
}

void MainMenuScene::menuSettingCallback(cocos2d::Ref* pSender){

}

void MainMenuScene::menuExitCallback(cocos2d::Ref* pSender){
	Director::getInstance()->end();
}
