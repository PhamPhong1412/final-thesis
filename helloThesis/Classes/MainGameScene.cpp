#include "MainGameScene.h"
#include "RankingScene.h"

Scene* MainGameScene::createScene(bool isTestMap,std::string mapText)
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = MainGameScene::create();
	
    GameConfig::isTestMap = isTestMap;
	if (isTestMap)
	{
        
		layer->initWithTestGame(mapText, layer);
	}
	else
	{
		layer->initWithRealGame(mapText, layer);
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

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	GameBackgroundLayer* backgroundLayder = new GameBackgroundLayer();
	//backgroundLayder->init(gameMap->backgroundName, gameMap->background);
	backgroundLayder->init();
	//this->addChild(backgroundLayder);

	//auto gamePlayLayer = GamePlayLayer::create();
	

#pragma region menu
	cocos2d::Vector<MenuItem*> items;

	auto mSettingButton = MenuItemImage::create("Pause1.png", "Pause2.png", CC_CALLBACK_1(MainGameScene::menuSettingCallback, this));
	mSettingButton->setAnchorPoint(Vec2(1, 1));
	mSettingButton->setScale(BUTTON_SIZE / mSettingButton->getContentSize().width);
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

void MainGameScene::initWithTestGame(std::string mapText,Layer *Parentlayer)
{
	
	auto testGamePlayLayer = new TestGamePlayLayer();
	testGamePlayLayer->init(mapText, Parentlayer);
	this->addChild(testGamePlayLayer);
}

void MainGameScene::initWithRealGame(std::string mapText,Layer *Parentlayer)
{
	
	auto realGamePlayLayer = new RealGamePlayLayer();
	realGamePlayLayer->init(mapText,Parentlayer);
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
