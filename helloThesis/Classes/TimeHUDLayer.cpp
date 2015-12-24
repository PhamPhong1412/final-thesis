//
//  TimeHUDLayer.cpp
//  Run
//
//  Created by TFLAT iOS Developer on 12/24/15.
//
//

#include "TimeHUDLayer.h"

TimeHUDLayer::TimeHUDLayer(Layer* parent) : HUDLayer(parent,true){
    this->init();
}

TimeHUDLayer::~TimeHUDLayer(){
    
}

// on "init" you need to initialize your instance
bool TimeHUDLayer::init()
{
//    background = Sprite::create("HelloWorld.png");
//    background->setPosition(Vec2(DESIGN_SCREEN_WIDTH / 2, DESIGN_SCREEN_HEIGHT / 2));
//    this->addChild(background);
    
    timeLabel = Label::createWithTTF("0", "Marker Felt.ttf", 30);
    timeLabel->setAnchorPoint(Vec2(0.5, 1));
    // position the label on the center of the screen
    timeLabel->setPosition(Vec2(DESIGN_SCREEN_WIDTH / 2, DESIGN_SCREEN_HEIGHT - 40));
    timeLabel->setTextColor(Color4B(255, 195, 0, 255));
    this->addChild(timeLabel);

    
    cocos2d::Vector<MenuItem*> items;
    
    auto mBackButton = MenuItemImage::create("ExitNormal.png", "ExitSelected.png", CC_CALLBACK_0(TimeHUDLayer::menuBackCallback, this));
    mBackButton->setAnchorPoint(Vec2(0, 1));
    mBackButton->setScale(70 / mBackButton->getContentSize().width);
    mBackButton->setPosition(Vec2(DESIGN_SCREEN_WIDTH/2, DESIGN_SCREEN_HEIGHT/2));
    items.pushBack(mBackButton);
    
    auto menu = Menu::createWithArray(items);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    
    return true;
}

void TimeHUDLayer::setTimeLabel(float time)
{
    timeLabel->setString(cocos2d::StringUtils::format("%f",time));
}

void TimeHUDLayer::menuBackCallback()
{
    exit();
}