#include "MainGameScene.h"
#include "RankingScene.h"

Scene* MainGameScene::createScene(bool isTestMap)
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = MainGameScene::create();
	
	layer->setTag(111);
	if (isTestMap)
	{
		layer->initWithTestGame();
	}
	else
	{
		std::string test = DBContext::get("map_test");
		layer->initWithRealGame(test);
	}
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
	int i = this->getTag();

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	GameBackgroundLayer* backgroundLayder = new GameBackgroundLayer();
	//backgroundLayder->init(gameMap->backgroundName, gameMap->background);
	backgroundLayder->init();
	//this->addChild(backgroundLayder);

	//auto gamePlayLayer = GamePlayLayer::create();
	

#pragma region menu
	cocos2d::Vector<MenuItem*> items;

	auto mBackButton = MenuItemImage::create("ExitNormal.png", "ExitSelected.png", CC_CALLBACK_1(MainGameScene::menuBackCallback, this));
	mBackButton->setAnchorPoint(Vec2(0, 1));
	mBackButton->setScale(70 / mBackButton->getContentSize().width);
	mBackButton->setPosition(Vec2(origin.x + 15, origin.y + visibleSize.height - 15));
	items.pushBack(mBackButton);

	auto mSettingButton = MenuItemImage::create("ExitNormal.png", "ExitSelected.png", CC_CALLBACK_1(MainGameScene::menuSettingCallback, this));
	mSettingButton->setAnchorPoint(Vec2(1, 1));
	mSettingButton->setScale(70 / mBackButton->getContentSize().width);
	mSettingButton->setPosition(Vec2(origin.x + visibleSize.width- 15, origin.y + visibleSize.height - 15));
	items.pushBack(mSettingButton);

    auto menu = Menu::createWithArray(items);
    menu->setPosition(Vec2::ZERO);
	menu->setTag(TAG_BUTTON_LAYER);
    this->addChild(menu, 1);
#pragma endregion 
    
	isPause = false;
	return true;
}

void MainGameScene::initWithTestGame()
{
	GameConfig::isTestMap = true;
	auto testGamePlayLayer = new TestGamePlayLayer();
	std::string test = DBContext::get("map_test");
	testGamePlayLayer->init(test);
	this->addChild(testGamePlayLayer);
}

void MainGameScene::initWithRealGame(std::string mapText)
{
	GameConfig::isTestMap = false;
	auto realGamePlayLayer = new RealGamePlayLayer();
	realGamePlayLayer->init(mapText);
	this->addChild(realGamePlayLayer);
}

void MainGameScene::menuBackCallback(cocos2d::Ref *pSender)
{
	if (GameConfig::isTestMap)
	{
		auto mapMakingScene = MapMakingScene::createScene();
		Director::getInstance()->replaceScene(mapMakingScene);
	}
	else
	{
		auto rankScene = RankingScene::createScene();
		Director::getInstance()->replaceScene(rankScene);
	}
    
}

void MainGameScene::menuPlayCallback(cocos2d::Ref* pSender){

}

void MainGameScene::menuSettingCallback(cocos2d::Ref *pSender)
{
	//if (!isPause){
		//InGameSettingLayer* settingLayer = InGameSettingLayer::create(this);
		//this->addChild(settingLayer);

	InGameSettingLayer* settingLayer = new InGameSettingLayer(this);
	this->addChild(settingLayer);
		isPause = true;
	//}
}
