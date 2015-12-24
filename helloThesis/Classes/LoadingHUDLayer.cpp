//
//  TimeHUDLayer.cpp
//  Run
//
//  Created by TFLAT iOS Developer on 12/24/15.
//
//

#include "LoadingHUDLayer.h"

LoadingHUDLayer::LoadingHUDLayer(Layer* parent) : HUDLayer(parent, false){
    this->init();
}

LoadingHUDLayer ::~LoadingHUDLayer(){
    
}

// on "init" you need to initialize your instance
bool LoadingHUDLayer::init()
{
	auto origin = Director::getInstance()->getVisibleOrigin();
    auto timeLabel = Label::createWithTTF("Loading...", "Marker Felt.ttf", 30);
    timeLabel->setAnchorPoint(Vec2(0.5, 1));
    // position the label on the center of the screen
    timeLabel->setPosition(Vec2(origin.x + DESIGN_SCREEN_WIDTH / 2 - 53, origin.y + DESIGN_SCREEN_HEIGHT - 40 - 18));
    timeLabel->setTextColor(Color4B(255, 195, 0, 255));
    this->addChild(timeLabel);
    
	auto mBody = CSLoader::createNode(FileUtils::getInstance()->fullPathForFilename("loading.csb"));
	auto mAnimation = CSLoader::createTimeline(FileUtils::getInstance()->fullPathForFilename("loading.csb"));
	mAnimation->play("load", true);
	mBody->runAction(mAnimation);
	mBody->setAnchorPoint(Vec2(0.5, 0.5));
	mBody->setPosition(origin.x + DESIGN_SCREEN_WIDTH / 2 - 53, origin.y + DESIGN_SCREEN_HEIGHT / 2 - 18);
	
	this->addChild(mBody);

    return true;
}

void LoadingHUDLayer::exitLoading()
{
	exit();
}
