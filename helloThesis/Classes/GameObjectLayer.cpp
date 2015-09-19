//#include "GameBackgroundLayer.h"
//
//
//Scene* GameBackgroundLayer::createScene()
//{
//	// 'scene' is an autorelease object
//	auto scene = Scene::create();
//
//	// 'layer' is an autorelease object
//	auto layer = GameBackgroundLayer::create();
//
//	// add layer as a child to scene
//	scene->addChild(layer);
//
//	// return the scene
//	return scene;
//}
//
//// on "init" you need to initialize your instance
//bool GameBackgroundLayer::init(std::string backgroundID)
//{
//	if (!Layer::init())
//	{
//		return false;
//	}
//	
//	Size visibleSize = Director::getInstance()->getVisibleSize();
//
//	this->scheduleUpdate();
//
//	return true;
//}
//
//void GameBackgroundLayer::update(float delta){
//
//
//
//}
