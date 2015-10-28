//
//  ShopScene.cpp
//  GameRun
//
//  Created by TFLAT iOS Developer on 10/28/15.
//
//

#include "ShopScene.h"
#include "MainMenuScene.h"

Scene* ShopScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = ShopScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool ShopScene::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Layer::init())
    {
        return false;
    }
    
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
    auto mBackGround = Sprite::create("bg3.png");
    mBackGround->setScale(visibleSize.height/mBackGround->getContentSize().height);
    mBackGround->setAnchorPoint(Vec2(0.5,0.5));
    mBackGround->setPosition((origin.x +visibleSize.width)/2, (origin.y +visibleSize.height)/2);
    addChild(mBackGround);
    
    initListVertical();
    initListRoot();
    initButton();
    
    return true;
}

void ShopScene::initButton()
{

    mBackButton = MenuItemImage::create("ExitNormal.png", "ExitSelected.png", CC_CALLBACK_1(ShopScene::menuBackCallback, this));
    mBackButton->setAnchorPoint(Vec2(0,0));
    mBackButton->setScale(70/mBackButton->getContentSize().width);
    mBackButton->setPosition(Vec2(origin.x + 15,origin.y +15));
    cocos2d::Vector<MenuItem*> items;
    items.pushBack(mBackButton);
    auto menu = Menu::createWithArray(items);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

}

void ShopScene::initListChild()
{
    mListButtonChild = ui::ListView::create();
    mListButtonChild->setDirection(ui::ScrollView::Direction::HORIZONTAL);
    mListButtonChild->setClippingEnabled(false);
    mListButtonChild->setPosition(Vec2(0,origin.y));
    mListButtonChild->setContentSize(Size(70 + origin.x + 20,visibleSize.height));
    
    mListButtonChild->setItemsMargin(10);
    mListButtonChild->addEventListener((ui::ListView::ccListViewCallback)CC_CALLBACK_2(ShopScene::selectedItemChildListEvent, this));
    mListButtonChild->setBackGroundColorType(cocos2d::ui::LayoutBackGroundColorType::SOLID);
    mListButtonChild->setScrollBarEnabled(false);
    mListButtonChild->setBackGroundColor(Color3B( 0, 255, 0));
    mListButtonChild->setVisible(false);
    addChild(mListButtonChild);
}

void ShopScene::initListRoot()
{
    mListButonRoot = ui::ListView::create();
    mListButonRoot->setDirection(ui::ScrollView::Direction::HORIZONTAL);
    mListButonRoot->setClippingEnabled(true);
    mListButonRoot->setBounceEnabled(true);
    mListButonRoot->setPosition(Vec2(origin.x + mListVertical->getContentSize().width ,origin.y + 70/GameConfig::scale));
    mListButonRoot->setContentSize(Size(visibleSize.width - mListVertical->getContentSize().width,70/GameConfig::scale));
    
    for (int i =0 ; i<7 ; i++) {
        ui::Button *button = ui::Button::create(getNameWithNumber(i));
        button->setScale(GameConfig::scale);
        mListButonRoot->pushBackCustomItem(button);
    }
    
    mListButonRoot->setItemsMargin(10);
    mListButonRoot->addEventListener((ui::ListView::ccListViewCallback)CC_CALLBACK_2(ShopScene::selectedItemRootListEvent, this));
    mListButonRoot->setBackGroundColorType(cocos2d::ui::LayoutBackGroundColorType::SOLID);
    mListButonRoot->setScrollBarEnabled(false);
    mListButonRoot->setBackGroundColor(Color3B( 0, 255, 0));
    addChild(mListButonRoot);
}

void ShopScene::initListVertical()
{
    mListVertical = ui::ListView::create();
    mListVertical->setAnchorPoint(Vec2(0,1));
    mListVertical->setDirection(ui::ScrollView::Direction::VERTICAL);
    mListVertical->setClippingEnabled(true);
    mListVertical->setBounceEnabled(true);
    mListVertical->setPosition(Vec2(origin.x,origin.y+visibleSize.height));
    mListVertical->setContentSize(Size(70/GameConfig::scale,visibleSize.height - 70/GameConfig::scale - 15));
//    for (int i =0 ; i<mMapNameItem.size() ; i++) {
        for (int i =0 ; i<7 ; i++) {
        ui::Button *button = ui::Button::create(getNameWithNumber(i));
        button->setScale(GameConfig::scale);
        mListVertical->pushBackCustomItem(button);
    }
    
    mListVertical->setItemsMargin(10);
    mListVertical->addEventListener((ui::ListView::ccListViewCallback)CC_CALLBACK_2(ShopScene::selectedItemVerticalListEvent, this));
    mListVertical->setBackGroundColorType(cocos2d::ui::LayoutBackGroundColorType::SOLID);
    mListVertical->setScrollBarEnabled(false);
    mListVertical->setBackGroundColor(Color3B( 0, 255, 0));
    addChild(mListVertical);

}

void ShopScene::menuBackCallback(cocos2d::Ref *pSender)
{
    auto mainScene = MainMenuScene::createScene();
    Director::getInstance()->replaceScene(mainScene);
}

void ShopScene::selectedItemVerticalListEvent(Ref *sender, ui::ListView::EventType type)
{
        ui::ListView *listView = static_cast<ui::ListView *>(sender);
    
        switch (type)
        {
            case ui::ListView::EventType::ON_SELECTED_ITEM_START:
    
                break;
            case ui::ListView::EventType::ON_SELECTED_ITEM_END:
                
                break;
            default:
                break;
        }
}

void ShopScene::selectedItemRootListEvent(Ref *sender, ui::ListView::EventType type)
{
//    ui::ListView *listView = static_cast<ui::ListView *>(sender);
//    
//    switch (type) {
//        case ui::ListView::EventType::ON_SELECTED_ITEM_START:
//            
//            break;
//        case ui::ListView::EventType::ON_SELECTED_ITEM_END:
//            if (mCheckRootItem) {
//                CCLOG("go to child item with index root = %ld",listView->getCurSelectedIndex());
//                mListButtonChild->removeAllChildren();
//                tVectorNameChildItem = mMapNameItem[(int)listView->getCurSelectedIndex()];
//                for (int i = 0 ; i < tVectorNameChildItem.size(); i++) {
//                    ui::Button *button = ui::Button::create(tVectorNameChildItem[i]);
//                    button->setScale(GameConfig::scale);
//                    mListButtonChild->pushBackCustomItem(button);
//                }
//                listView->setVisible(false);
//                mListButtonChild->setVisible(true);
//                mCheckRootItem = false;
//            }
//            break;
//            
//        default:
//            break;
//    }
    
    
}

void ShopScene::selectedItemChildListEvent(Ref *sender, ui::ListView::EventType type)
{
//    ui::ListView *listView = static_cast<ui::ListView *>(sender);
//    switch (type) {
//        case ui::ListView::EventType::ON_SELECTED_ITEM_START:
//            
//            break;
//        case ui::ListView::EventType::ON_SELECTED_ITEM_END:
//            
//            if (listView->getCurSelectedIndex() != 0) {
//                CCLOG("index Child = %ld",listView->getCurSelectedIndex());
//                mCurrentNameChild = tVectorNameChildItem[(int)listView->getCurSelectedIndex()];
//            }
//            else
//            {
//                mCheckRootItem = true;
//                CCLOG("Return Root item");
//                listView->setVisible(false);
//                mListButonRoot->setVisible(true);
//            }
//            
//            break;
//            
//        default:
//            break;
//    }
}


string ShopScene::getNameWithNumber(int number)
{
    string rName="";
    switch (number) {
        case 0:
            rName ="castle.png";
            break;
        case 1:
            rName ="boxItem.png";
            break;
        case 2:
            rName ="fence.png";
            break;
        case 3:
            rName ="signRight.png";
            break;
        case 4:
            rName ="tochLit.png";
            break;
        case 5:
            rName ="liquidWaterTop_mid.png";
            break;
        case 6:
            rName ="stoneHalf.png";
            break;
        default:
            break;
    }
    return rName;
}
