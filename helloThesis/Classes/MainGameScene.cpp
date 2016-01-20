#include "MainGameScene.h"
#include "RankingScene.h"

Scene* MainGameScene::createScene(bool isTestMap, std::string mapText, HttpShortMapInfo mapInfo)
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
		layer->initWithRealGame(mapText, layer, mapInfo);
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

	auto mBackGround = Sprite::create("background.png");
	mBackGround->setScale(visibleSize.width / mBackGround->getContentSize().width, visibleSize.height / mBackGround->getContentSize().height);
	mBackGround->setAnchorPoint(Vec2(0.5, 0.5));
	mBackGround->setPosition(origin.x + (visibleSize.width) / 2, origin.y + (visibleSize.height) / 2);
	addChild(mBackGround);

	//auto gamePlayLayer = GamePlayLayer::create();
    
    mTimeLabel = Label::createWithTTF("0", "Marker Felt.ttf", 30);
    mTimeLabel->setAnchorPoint(Vec2(0.5, 1));
    // position the label on the center of the screen
    mTimeLabel->setPosition(Vec2(origin.x + DESIGN_SCREEN_WIDTH / 2  , origin.y + DESIGN_SCREEN_HEIGHT - 40 ));
    mTimeLabel->setTextColor(Color4B(255, 195, 0, 255));
	mTimeLabel->setZOrder(100);
    this->addChild(mTimeLabel);
    

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
    testGamePlayLayer->setDelegate(this);
	this->addChild(testGamePlayLayer);
}

void MainGameScene::initWithRealGame(std::string mapText, Layer *Parentlayer, HttpShortMapInfo mapInfo)
{
	auto realGamePlayLayer = new RealGamePlayLayer();
	realGamePlayLayer->init(mapText,Parentlayer, mapInfo);
    realGamePlayLayer->setDelegate(this);
    
	this->addChild(realGamePlayLayer);
}

void MainGameScene::testUpdateTime(float time)
{
    if (time == 0) {
        mTimeLabel->setString("");
    }
    else
    {
       mTimeLabel->setString(StringUtils::format("%.2f",time));
    }
    
}

void MainGameScene::realUpdateTime(float time)
{
    if (time == 0) {
        mTimeLabel->setString("");
    }
    else
    {
        mTimeLabel->setString(StringUtils::format("%.2f",time));
    }
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
