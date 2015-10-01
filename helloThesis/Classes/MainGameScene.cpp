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
	this->gameMap = new GameMap();
	gameMap->load("test");

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	GameBackgroundLayer* backgroundLayder = new GameBackgroundLayer();
	backgroundLayder->init(gameMap->backgroundName, gameMap->background);
	this->addChild(backgroundLayder);

	auto gamePlayLayer = GamePlayLayer::create();
	//gamePlayLayer->init();
	this->addChild(gamePlayLayer);

	return true;
}


void MainGameScene::menuPlayCallback(cocos2d::Ref* pSender){

}
