//
//  RateHUDLayer.cpp
//  MyRun
//
//  Created by Thien Banh on 12/29/15.
//
//

#include "RateHUDLayer.h"
#include "RankingScene.h"

// on "init" you need to initialize your instance
RateHUDLayer::RateHUDLayer(Layer* parent, float time) : HUDLayer(parent, false, -53,-18){
    this->init(-53,-18, time);
}

RateHUDLayer::~RateHUDLayer(){
    
}

// on "init" you need to initialize your instance
bool RateHUDLayer::init(float x, float y, float time)
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();
    
    background = Sprite::create("WidthHeightChoose.png");
    background->setPosition(Vec2(origin.x + DESIGN_SCREEN_WIDTH / 2 + x, origin.y + DESIGN_SCREEN_HEIGHT / 2 + y));
    background->setScale(0.5,0.7);
    this->addChild(background);
    
    auto infoLabel = Label::createWithTTF(StringUtils::format("Time: %.2f", time), "Marker Felt.ttf", 30);
    infoLabel->setAnchorPoint(Vec2(0.5, 0.5));
    // position the label on the center of the screen
    infoLabel->setPosition(Vec2(origin.x + DESIGN_SCREEN_WIDTH / 2 + x , origin.y + visibleSize.height/2 + 100 + y));
    infoLabel->setTextColor(Color4B(255, 195, 0, 255));
    this->addChild(infoLabel);
    
    cocos2d::Vector<MenuItem*> items;
    
    mStar1Button = MenuItemImage::create("StarShadow.png", "Star.png", CC_CALLBACK_0(RateHUDLayer::menuStar1Callback, this));
    mStar1Button->setAnchorPoint(Vec2(0, 0));
    mStar1Button->setScale(BUTTON_SIZE / mStar1Button->getContentSize().width);
    mStar1Button->setPosition(Vec2(origin.x + DESIGN_SCREEN_WIDTH / 3 + x,origin.y + visibleSize.height/2 + y));
    items.pushBack(mStar1Button);
    
    mStar2Button  = MenuItemImage::create("StarShadow.png", "Star.png", CC_CALLBACK_0(RateHUDLayer::menuStar2Callback, this));
    mStar2Button->setAnchorPoint(Vec2(0.5, 0));
    mStar2Button->setScale(BUTTON_SIZE / mStar2Button->getContentSize().width);
    mStar2Button->setPosition(Vec2(origin.x + DESIGN_SCREEN_WIDTH / 2 + x,origin.y+ visibleSize.height/2  + y));
    items.pushBack(mStar2Button);
    
    mStar3Button = MenuItemImage::create("StarShadow.png", "Star.png", CC_CALLBACK_0(RateHUDLayer::menuStar3Callback, this));
    mStar3Button->setAnchorPoint(Vec2(1, 0));
    mStar3Button->setScale(BUTTON_SIZE / mStar3Button->getContentSize().width);
    mStar3Button->setPosition(Vec2(origin.x + DESIGN_SCREEN_WIDTH *2 / 3 + x,origin.y+visibleSize.height/2 + y));
    items.pushBack(mStar3Button);
    
    mStar1Button->unselected();
    mStar2Button->unselected();
    mStar3Button->unselected();
    
    auto mBackButton = MenuItemImage::create("ExitNormal.png", "ExitSelected.png", CC_CALLBACK_0(RateHUDLayer::menuBackCallback, this));
    mBackButton->setAnchorPoint(Vec2(0.5, 0));
    mBackButton->setScale(BUTTON_SIZE / mBackButton->getContentSize().width);
    mBackButton->setPosition(Vec2(origin.x + DESIGN_SCREEN_WIDTH / 3 + x,origin.y+ 130 + y));
    items.pushBack(mBackButton);
    
    auto mReplayButton = MenuItemImage::create("Replay1.png", "Replay2.png", CC_CALLBACK_0(RateHUDLayer::menuReplayCallback, this));
    mReplayButton->setAnchorPoint(Vec2(0.5, 0));
    mReplayButton->setScale(BUTTON_SIZE / mReplayButton->getContentSize().width);
    mReplayButton->setPosition(Vec2(origin.x + DESIGN_SCREEN_WIDTH / 2 + x,origin.y+ 130 + y));
    items.pushBack(mReplayButton);
    
    auto mNextButton = MenuItemImage::create("AddNormal.png", "AddSelected.png", CC_CALLBACK_0(RateHUDLayer::menuNextCallback, this));
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

void RateHUDLayer::menuStar1Callback()
{
    if (!mStar1Button->isSelected()) {
        mStar1Button->selected();
        mStar2Button->unselected();
        mStar3Button->unselected();
    }
}

void RateHUDLayer::menuStar2Callback()
{
    if (!mStar2Button->isSelected()) {
        mStar1Button->selected();
        mStar2Button->selected();
        mStar3Button->unselected();
    }
}

void RateHUDLayer::menuStar3Callback()
{
    if (!mStar3Button->isSelected()) {
        mStar1Button->selected();
        mStar2Button->selected();
        mStar3Button->selected();
    }
}

void RateHUDLayer::menuReplayCallback()
{
    
}

void RateHUDLayer::menuNextCallback()
{
    int number = 0;
    
    if (mStar1Button->isSelected() && !mStar2Button->isSelected()) {
        number = 1;
    }
    else if(mStar2Button->isSelected() && !mStar3Button->isSelected())
    {
       number = 2;
    }
    else if (mStar3Button->isSelected())
    {
        number = 3;
    }
    
    mDelegate->ratePress(number);
}
void RateHUDLayer::menuBackCallback()
{
    auto rankScene = RankingScene::createScene();
    Director::getInstance()->replaceScene(rankScene);
    mDelegate->exitBack();
}
