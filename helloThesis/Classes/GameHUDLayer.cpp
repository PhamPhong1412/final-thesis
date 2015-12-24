#include "GameHUDLayer.h"

// on "init" you need to initialize your instance
GameHUDLayer::GameHUDLayer(Layer* parent) : HUDLayer(parent, false){
	this->init();
}

GameHUDLayer::~GameHUDLayer(){

}

// on "init" you need to initialize your instance
bool GameHUDLayer::init()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();
    
	background = Sprite::create("Windown1.png");
	background->setPosition(Vec2(origin.x + DESIGN_SCREEN_WIDTH / 2 - 53, origin.y + DESIGN_SCREEN_HEIGHT / 2-18));
	background->setScale(0.5);
	this->addChild(background);

	cocos2d::Vector<MenuItem*> items;

	auto mBackButton = MenuItemImage::create("ExitNormal.png", "ExitSelected.png", CC_CALLBACK_0(GameHUDLayer::menuBackCallback, this));
	mBackButton->setAnchorPoint(Vec2(0.5, 0));
	mBackButton->setScale(70 / mBackButton->getContentSize().width);
	mBackButton->setPosition(Vec2(origin.x + DESIGN_SCREEN_WIDTH / 3 - 53,origin.y+ 100 - 18));
	items.pushBack(mBackButton);

	auto mNextButton = MenuItemImage::create("AddNormal.png", "AddSelected.png", CC_CALLBACK_0(GameHUDLayer::menuNextCallback, this));
	mNextButton->setAnchorPoint(Vec2(0.5, 0));
	mNextButton->setScale(70 / mNextButton->getContentSize().width);
	mNextButton->setPosition(Vec2(origin.x + (DESIGN_SCREEN_WIDTH * 2) / 3 - 53,origin.y + 100 - 18));
	items.pushBack(mNextButton);

	auto menu = Menu::createWithArray(items);
	menu->setPosition(Vec2::ZERO);
	menu->setTag(TAG_BUTTON_LAYER);
	this->addChild(menu, 1);

	return true;
}

void GameHUDLayer::menuNextCallback()
{
	mDelegate->saveMap();
}
void GameHUDLayer::menuBackCallback()
{
	mDelegate->exitBack();
}


