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
	mSettingButton->setAnchorPoint(Vec2(0, 1));
	mSettingButton->setScale(70 / mBackButton->getContentSize().width);
	mSettingButton->setPosition(Vec2(origin.x + visibleSize.width- 15, origin.y + visibleSize.height - 15));
	items.pushBack(mSettingButton);

    auto menu = Menu::createWithArray(items);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
#pragma endregion 
    
	isPause = false;
	return true;
}

void MainGameScene::initWithTestGame()
{
	isTestMap = true;
	auto testGamePlayLayer = new TestGamePlayLayer();
	std::string test = DBContext::get("map_test");
	testGamePlayLayer->init(test);
	this->addChild(testGamePlayLayer);
}

void MainGameScene::initWithRealGame(std::string mapText)
{
	isTestMap = false;
	auto realGamePlayLayer = new RealGamePlayLayer();
	realGamePlayLayer->init(mapText);
	this->addChild(realGamePlayLayer);
}

void MainGameScene::menuBackCallback(cocos2d::Ref *pSender)
{
	if (isTestMap)
	{
		auto mapMakingScene = MapMakingScene::createScene();
		((MapMakingScene*)mapMakingScene)->setIsNewMap(true);
		Director::getInstance()->replaceScene(mapMakingScene);
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
