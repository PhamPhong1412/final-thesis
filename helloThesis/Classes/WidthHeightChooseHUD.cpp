//
//  WidthHeightChooseHUD.cpp
//  GameRun
//
//  Created by Thien Banh on 11/14/15.
//
//

#include "WidthHeightChooseHUD.h"
#include "MainMenuScene.h"

WidthHeightChooseHUD::WidthHeightChooseHUD(Layer* parent,bool canExit, bool withBackground) : HUDLayer(parent,canExit){
	this->init(withBackground);
}

WidthHeightChooseHUD::~WidthHeightChooseHUD(){
    
}

// on "init" you need to initialize your instance
bool WidthHeightChooseHUD::init(bool withBackground)
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();
	if (!withBackground)
	{
		background = Sprite::create("bg3.png");
        background->setAnchorPoint(Vec2(0.5,0.5));
		background->setPosition(Vec2(origin.x + visibleSize.width / 2,origin.y + visibleSize.height / 2));
		background->setScale(visibleSize.width / background->getContentSize().width, visibleSize.height / background->getContentSize().height);
		this->addChild(background);
	}
    
	haveLocalMap = DBContext::keyExist("map_test");

	auto boxSprite = Sprite::create("WidthHeightChoose.png");
	boxSprite->setPosition(Vec2(origin.x + visibleSize.width / 2,origin.y + visibleSize.height / 2));
	boxSprite->setScale((DESIGN_SCREEN_WIDTH / 1.5) / boxSprite->getContentSize().width, (DESIGN_SCREEN_HEIGHT / 1.5) / boxSprite->getContentSize().height);
	this->addChild(boxSprite);

	mWidthEditBox = ui::EditBox::create(Size(DESIGN_SCREEN_WIDTH / 3, 50), ui::Scale9Sprite::create("TextField.png"));
    mWidthEditBox->setMaxLength(3);
	mWidthEditBox->setFontSize(20);
	mWidthEditBox->setAnchorPoint(Vec2(0.5,0.5));
	mWidthEditBox->setPosition(Vec2(origin.x + boxSprite->getPosition().x,origin.y + DESIGN_SCREEN_HEIGHT/2 ));
    mWidthEditBox->setInputMode(cocos2d::ui::EditBox::InputMode::NUMERIC );
	mWidthEditBox->setPlaceholderFontColor(Color3B::WHITE);
    mWidthEditBox->setPlaceholderFontSize(20);
    mWidthEditBox->setPlaceHolder("Input number tile of width");


	mHeightEditBox = ui::EditBox::create(Size(DESIGN_SCREEN_WIDTH / 3, 50), ui::Scale9Sprite::create("TextField.png"));
    mHeightEditBox->setMaxLength(3);
	mHeightEditBox->setFontSize(20);
	mHeightEditBox->setAnchorPoint(Vec2(0.5, 0.5));
	mHeightEditBox->setPosition(Vec2(origin.x + boxSprite->getPosition().x,origin.y + DESIGN_SCREEN_HEIGHT/2 - 60));
    mHeightEditBox->setInputMode(cocos2d::ui::EditBox::InputMode::NUMERIC );
    mHeightEditBox->setPlaceHolder("Input number tile of height");
	mHeightEditBox->setPlaceholderFontColor(Color3B::WHITE);
    mHeightEditBox->setPlaceholderFontSize(20);
	mHeightEditBox->setReturnType(ui::EditBox::KeyboardReturnType::DONE);

    this->addChild(mHeightEditBox);
    this->addChild(mWidthEditBox);

	infoLabel = Label::createWithTTF("Do u want to contine your map...", "Marker Felt.ttf", 30);
	infoLabel->setAnchorPoint(Vec2(0.5, 1));
	// position the label on the center of the screen
	infoLabel->setPosition(Vec2(origin.x + DESIGN_SCREEN_WIDTH / 2, origin.y + visibleSize.height - 100));
	infoLabel->setTextColor(Color4B(255, 195, 0, 255));
	this->addChild(infoLabel);
    
    cocos2d::Vector<MenuItem*> items;
    
    mBackButton = MenuItemImage::create("ExitNormal.png", "ExitSelected.png", CC_CALLBACK_0(WidthHeightChooseHUD::menuBackCallback, this));
    mBackButton->setAnchorPoint(Vec2(0.5, 0));
    mBackButton->setScale(BUTTON_SIZE / mBackButton->getContentSize().width);
    mBackButton->setPosition(Vec2(origin.x + DESIGN_SCREEN_WIDTH/4,origin.y + 50));
    items.pushBack(mBackButton);
    
    mNewButton = MenuItemImage::create("AddNormal.png", "AddSelected.png", CC_CALLBACK_0(WidthHeightChooseHUD::menuNewCallback, this));
    mNewButton->setAnchorPoint(Vec2(0.5, 0));
    mNewButton->setScale(BUTTON_SIZE / mNewButton->getContentSize().width);
    mNewButton->setPosition(Vec2(origin.x + DESIGN_SCREEN_WIDTH/2,origin.y + 50));
    items.pushBack(mNewButton);
    
    mNextButton = MenuItemImage::create("Next2.png", "Next1.png", CC_CALLBACK_0(WidthHeightChooseHUD::menuNextCallback, this));
    mNextButton->setAnchorPoint(Vec2(0.5, 0));
    mNextButton->setScale(BUTTON_SIZE / mNextButton->getContentSize().width);
    mNextButton->setPosition(Vec2((origin.x + DESIGN_SCREEN_WIDTH*3)/4, origin.y + 50 ));
    items.pushBack(mNextButton);
    
    auto menu = Menu::createWithArray(items);
    menu->setPosition(Vec2::ZERO);
	
    this->addChild(menu, 1);

	if (haveLocalMap)
	{
		mHeightEditBox->setVisible(false);
		mWidthEditBox->setVisible(false);
		
	}
    else
    {
        mNewButton->setVisible(false);
		infoLabel->setString("Add info of your map");
    }
    
    return true;
}

void WidthHeightChooseHUD::menuNewCallback()
{
    mHeightEditBox->setVisible(true);
    mWidthEditBox->setVisible(true);
    infoLabel->setString("Add info of your map");
    mNewButton->setVisible(false);
    haveLocalMap = false;
    
}

void WidthHeightChooseHUD::menuNextCallback()
{
	
	if (haveLocalMap)
	{
		mDelegate->loadLocalMap();
		exit();
	}
	else
	{
		int witdh = 0;
		int height = 0;
		if (mWidthEditBox->getText()) {

		}

		if (Utility::isNumber(mWidthEditBox->getText()) && Utility::isNumber(mHeightEditBox->getText())){
			witdh = std::stoi(mWidthEditBox->getText());
			height = std::stoi(mHeightEditBox->getText());
		}
		else{
			witdh = 40;
			height = 40;
		}

		if (witdh > 0 && height > 0) {
			mDelegate->exitBack(witdh, height);
			exit();
		}
		else
		{

		}
	}
	
}
void WidthHeightChooseHUD::menuBackCallback()
{   
	
    auto mainScene = MainMenuScene::createScene();
    Director::getInstance()->replaceScene(mainScene);
	
}