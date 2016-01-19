#include "GameHUDLayer.h"

// on "init" you need to initialize your instance
GameHUDLayer::GameHUDLayer(Layer* parent, float time) : HUDLayer(parent, false, -53,-18){
	this->init(-53,-18,time);
}

GameHUDLayer::~GameHUDLayer(){

}

// on "init" you need to initialize your instance
bool GameHUDLayer::init(float x, float y, float time)
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();
    
	background = Sprite::create("WidthHeightChoose.png");
	background->setPosition(Vec2(origin.x + DESIGN_SCREEN_WIDTH / 2 + x, origin.y + DESIGN_SCREEN_HEIGHT / 2 + y));
	background->setScale(0.5);
	this->addChild(background);

	auto infoLabel = Label::createWithTTF(StringUtils::format("Do u want to upload \n      this map...\n   Time: %f", time), "Marker Felt.ttf", 30);
	infoLabel->setAnchorPoint(Vec2(0.5, 0.5));
	// position the label on the center of the screen
	infoLabel->setPosition(Vec2(origin.x + DESIGN_SCREEN_WIDTH / 2 + x , origin.y + visibleSize.height/2 + 30 + y));
	infoLabel->setTextColor(Color4B(255, 195, 0, 255));
	this->addChild(infoLabel);

	cocos2d::Vector<MenuItem*> items;

	auto mBackButton = MenuItemImage::create("ExitNormal.png", "ExitSelected.png", CC_CALLBACK_0(GameHUDLayer::menuBackCallback, this));
	mBackButton->setAnchorPoint(Vec2(0.5, 0));
	mBackButton->setScale(BUTTON_SIZE / mBackButton->getContentSize().width);
	mBackButton->setPosition(Vec2(origin.x + DESIGN_SCREEN_WIDTH / 3 + x,origin.y+ 130 + y));
	items.pushBack(mBackButton);

	auto mNextButton = MenuItemImage::create("AddNormal.png", "AddSelected.png", CC_CALLBACK_0(GameHUDLayer::menuNextCallback, this));
	mNextButton->setAnchorPoint(Vec2(0.5, 0));
	mNextButton->setScale(BUTTON_SIZE / mNextButton->getContentSize().width);
	mNextButton->setPosition(Vec2(origin.x + (DESIGN_SCREEN_WIDTH * 2) / 3 + x,origin.y + 130 + y));
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


