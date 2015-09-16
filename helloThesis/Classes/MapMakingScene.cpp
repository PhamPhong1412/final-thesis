#include "MapMakingScene.h"


Scene* MapMakingScene::createScene()
{
     //'scene' is an autorelease object
    auto scene = Scene::create();
    
     //'layer' is an autorelease object
    auto layer = MapMakingScene::create();
    
     //add layer as a child to scene
    scene->addChild(layer);
    
     //return the scene
    return scene;
}

 //on "init" you need to initialize your instance
bool MapMakingScene::init()
{
    ////////////////////////////
     //1. super init first
    if (!Layer::init())
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    //SETUP SCROLL CONTAINER
    
    
    scrollContainer = CCLayer::create();
    scrollContainer->setAnchorPoint(Vec2(0,0));
    Sprite *background1;
    background1 = CCSprite::create("HelloWorld.png");
    background1->setScale(1);
    background1->setPosition(Vec2(100,600));
    scrollContainer->addChild(background1);
    
    Sprite *background2;
    background2 = CCSprite::create("HelloWorld.png");
    background2->setScale(1);
    background2->setPosition(Vec2(100,300));
    scrollContainer->addChild(background2);
    
    Sprite *background3;
    background3 = CCSprite::create("HelloWorld.png");
    background3->setScale(1);
    background3->setPosition(Vec2(100,0));
    scrollContainer->addChild(background3);
    
    scrollContainer->setPosition(Vec2(100,0));
    Size csize = Size(300,800);
    scrollContainer->setContentSize(csize);
    
    //SETUP SCROLL VIEW
    scrollView = ScrollView::create(visibleSize, scrollContainer);
    scrollView->setPosition(Vec2(0,0));
    scrollView->setDirection(ScrollView::Direction::VERTICAL);
    scrollView->setContentOffset(Vec2(0.f, (visibleSize.height - csize.height)), false);
    
    
    scrollContainer->retain();
    addChild(scrollView);
    
    
    TTFConfig config_font96("Marker Felt.ttf", 96);
    Label* startGame = Label::createWithTTF(config_font96, "Start game!");
    startGame->setPosition(Vec2(1,1));
    this->addChild(startGame);
    
    return true;
}
