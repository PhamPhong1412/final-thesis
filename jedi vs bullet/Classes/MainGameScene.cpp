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

	this->scheduleUpdate();
	initWithRealGame("");
	isPause = false;
	return true;
}

void MainGameScene::update(float delta){
	//if (GameConfig::gameFinished && !isPause)
	//{
	//	WidthHeightChooseHUD* chooseLayer = new WidthHeightChooseHUD(this, true);
	//	chooseLayer->setTag(2);
	//	chooseLayer->setDelegate(this);
	//	//this->removeChild(menu);
	//	this->addChild(chooseLayer);
	//	this->removeChildByTag(1);
	//	isPause = true;
	//}
}

void MainGameScene::initWithRealGame(std::string mapText)
{
	isTestMap = false;
	auto realGamePlayLayer = new RealGamePlayLayer();
	realGamePlayLayer->setTag(1);
	realGamePlayLayer->init(mapText);
	this->addChild(realGamePlayLayer);

}

void MainGameScene::exitBack()
{
	isPause = false;
	GameConfig::gameFinished = false;
	this->removeChildByTag(2);
	auto realGamePlayLayer = new RealGamePlayLayer();
	realGamePlayLayer->setTag(1);
	realGamePlayLayer->init("");
	this->addChild(realGamePlayLayer);
}

void MainGameScene::menuPlayCallback(cocos2d::Ref* pSender){

}