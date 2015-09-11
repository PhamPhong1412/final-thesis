#include "MapMakingScene.h"


Scene* MapMakingScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = MapMakingScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool MapMakingScene::init()
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

	return true;
}
