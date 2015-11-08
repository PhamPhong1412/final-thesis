#include "InGameSettingLayer.h"

InGameSettingLayer::InGameSettingLayer(Layer* parent) : HUDLayer(parent){
	this->init();
}

InGameSettingLayer::~InGameSettingLayer(){

}

// on "init" you need to initialize your instance
bool InGameSettingLayer::init()
{
	background = Sprite::create("HelloWorld.png");
	background->setPosition(Vec2(DESIGN_SCREEN_WIDTH / 2, DESIGN_SCREEN_HEIGHT / 2));
	this->addChild(background);

	cocos2d::Vector<MenuItem*> items;

	auto mBackButton = MenuItemImage::create("ExitNormal.png", "ExitSelected.png", CC_CALLBACK_0(InGameSettingLayer::menuBackCallback, this));
	mBackButton->setAnchorPoint(Vec2(0, 1));
	mBackButton->setScale(70 / mBackButton->getContentSize().width);
	mBackButton->setPosition(Vec2(DESIGN_SCREEN_WIDTH/2, DESIGN_SCREEN_HEIGHT/2));
	items.pushBack(mBackButton);

	auto menu = Menu::createWithArray(items);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	return true;
}

void InGameSettingLayer::menuBackCallback()
{
	exit();
}

