//
//  WidthHeightChooseHUD.cpp
//  GameRun
//
//  Created by Thien Banh on 11/14/15.
//
//

#include "WidthHeightChooseHUD.h"

WidthHeightChooseHUD::WidthHeightChooseHUD(Layer* parent,bool canExit) : HUDLayer(parent,canExit){
    this->init();
}

WidthHeightChooseHUD::~WidthHeightChooseHUD(){
    
}

// on "init" you need to initialize your instance
bool WidthHeightChooseHUD::init()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();
    
    background = Sprite::create("HelloWorld.png");
    background->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    background->setScale(visibleSize.width/background->getContentSize().width, visibleSize.height/background->getContentSize().height);
    this->addChild(background);
    
    mWidthEditBox = ui::EditBox::create(Size(visibleSize.width/2,50), "bg.png");
    mWidthEditBox->setMaxLength(3);
    mWidthEditBox->setPosition(Vec2(visibleSize.width/4,300));
    mWidthEditBox->setInputMode(cocos2d::ui::EditBox::InputMode::NUMERIC );
    mWidthEditBox->setPlaceHolder("Input number tile of width");
    
    mHeightEditBox = ui::EditBox::create(Size(visibleSize.width/2,50), "bg.png");
    mHeightEditBox->setMaxLength(3);
    mHeightEditBox->setPosition(Vec2(visibleSize.width/4,500));
    mHeightEditBox->setInputMode(cocos2d::ui::EditBox::InputMode::NUMERIC );
    mHeightEditBox->setPlaceHolder("Input number tile of height");
    
    this->addChild(mHeightEditBox);
    this->addChild(mWidthEditBox);
    
    cocos2d::Vector<MenuItem*> items;
    
    auto mBackButton = MenuItemImage::create("ExitNormal.png", "ExitSelected.png", CC_CALLBACK_0(WidthHeightChooseHUD::menuBackCallback, this));
    mBackButton->setAnchorPoint(Vec2(0, 1));
    mBackButton->setScale(70 / mBackButton->getContentSize().width);
    mBackButton->setPosition(Vec2(DESIGN_SCREEN_WIDTH/2, DESIGN_SCREEN_HEIGHT/2));
    items.pushBack(mBackButton);
    
    auto menu = Menu::createWithArray(items);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    
    return true;
}

void WidthHeightChooseHUD::menuBackCallback()
{   int witdh = 0;
    int height = 0;
    if (mWidthEditBox->getText()) {
        
    }
//	if (Utility::isNumber(mWidthEditBox->getText()) && Utility::isNumber(mHeightEditBox->getText())){
//		witdh = std::stoi(mWidthEditBox->getText());
//		height = std::stoi(mHeightEditBox->getText());
//	}
//	else{
		witdh = 300;
		height = 30;
//	}


    if (witdh > 0 && height > 0) {
        mDelegate->exitBack(witdh,height);
        exit();
    }
   else
   {
       
   }
}