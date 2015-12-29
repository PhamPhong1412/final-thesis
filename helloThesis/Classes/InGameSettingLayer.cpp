#include "InGameSettingLayer.h"
#include "MainMenuScene.h"

InGameSettingLayer::InGameSettingLayer(Layer* parent) : HUDLayer(parent,true,0,0){
	this->init();
}

InGameSettingLayer::~InGameSettingLayer(){

}

// on "init" you need to initialize your instance
bool InGameSettingLayer::init()
{
    auto origin = Director::getInstance()->getVisibleOrigin();
	background = Sprite::create("Pause.png");
	background->setPosition(Vec2(origin.x + DESIGN_SCREEN_WIDTH / 2,origin.y + DESIGN_SCREEN_HEIGHT / 2));
	this->addChild(background);

	auto infoLabel = Label::createWithTTF("PAUSE", "Marker Felt.ttf", 30);
	infoLabel->setAnchorPoint(Vec2(0.5, 0.5));
	// position the label on the center of the screen
	infoLabel->setPosition(Vec2(origin.x + DESIGN_SCREEN_WIDTH / 2 , origin.y + DESIGN_SCREEN_HEIGHT / 2 + 55));
	infoLabel->setTextColor(Color4B(255, 255, 255, 255));
	this->addChild(infoLabel);

	cocos2d::Vector<MenuItem*> items;

	auto mBackButton = MenuItemImage::create("Replay1.png", "Replay2.png", CC_CALLBACK_0(InGameSettingLayer::menuReplayCallback, this));
	mBackButton->setAnchorPoint(Vec2(0, 1));
	mBackButton->setScale(BUTTON_SIZE / mBackButton->getContentSize().width);
	mBackButton->setPosition(Vec2(origin.x + DESIGN_SCREEN_WIDTH/2 - 25, origin.y + DESIGN_SCREEN_HEIGHT/2));
	items.pushBack(mBackButton);

	auto mReplayButton = MenuItemImage::create("Home1.png", "Home2.png", CC_CALLBACK_0(InGameSettingLayer::menuHomeCallback, this));
    mReplayButton->setAnchorPoint(Vec2(0, 1));
    mReplayButton->setScale(BUTTON_SIZE / mReplayButton->getContentSize().width);
    mReplayButton->setPosition(Vec2(origin.x + DESIGN_SCREEN_WIDTH/2 + 100, origin.y + DESIGN_SCREEN_HEIGHT/2));
    items.pushBack(mReplayButton);
    
	auto mHomeButton = MenuItemImage::create("Play1.png", "Play2.png", CC_CALLBACK_0(InGameSettingLayer::menuBackCallback, this));
    mHomeButton->setAnchorPoint(Vec2(0, 1));
    mHomeButton->setScale(BUTTON_SIZE / mHomeButton->getContentSize().width);
    mHomeButton->setPosition(Vec2(origin.x + DESIGN_SCREEN_WIDTH/2 - 150, origin.y + DESIGN_SCREEN_HEIGHT/2));
    items.pushBack(mHomeButton);
    
	auto menu = Menu::createWithArray(items);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	return true;
}

void InGameSettingLayer::menuHomeCallback()
{
    auto homeScene = MainMenuScene::createScene();
    Director::getInstance()->replaceScene(homeScene);
}

void InGameSettingLayer::menuBackCallback()
{
	exit();
}

void InGameSettingLayer::menuReplayCallback()
{
	
}

