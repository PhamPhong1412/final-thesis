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

    
	//GameBackgroundLayer* backgroundLayder = new GameBackgroundLayer();
	//backgroundLayder->init(gameMap->backgroundName, gameMap->background);
	//this->addChild(backgroundLayder);

	//auto gamePlayLayer = GamePlayLayer::create();
	auto gamePlayLayer = new GamePlayLayer();

	std::string test = DBContext::get("map_test");

	gamePlayLayer->init(test);
	this->addChild(gamePlayLayer);
    
    auto mBackButton = MenuItemImage::create("ExitNormal.png", "ExitSelected.png", CC_CALLBACK_1(MainGameScene::menuBackCallback, this));
    mBackButton->setAnchorPoint(Vec2(0,1));
    mBackButton->setScale(70/mBackButton->getContentSize().width);
    mBackButton->setPosition(Vec2(origin.x + 15,origin.y + visibleSize.height -15));
    cocos2d::Vector<MenuItem*> items;
    items.pushBack(mBackButton);
    auto menu = Menu::createWithArray(items);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    
	return true;
}

void MainGameScene::menuBackCallback(cocos2d::Ref *pSender)
{
    auto mapMakingScene = MapMakingScene::createScene();
    Director::getInstance()->replaceScene(mapMakingScene);
}

void MainGameScene::menuPlayCallback(cocos2d::Ref* pSender){

}
