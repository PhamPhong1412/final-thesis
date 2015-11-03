#include "MainMenuScene.h"


Scene* MainMenuScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = MainMenuScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool MainMenuScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	std::string s = "abdf \t fwef";
	Utility::splitString(s, "\t");

    initButton();
	return true;
}

void MainMenuScene::initButton()
{
    auto mBackGround = Sprite::create("bg3.png");
    mBackGround->setScale(visibleSize.height/mBackGround->getContentSize().height);
    mBackGround->setAnchorPoint(Vec2(0.5,0.5));
    mBackGround->setPosition((origin.x +visibleSize.width)/2, (origin.y +visibleSize.height)/2);
    addChild(mBackGround);
    
    auto mNameSprite = Sprite::create("GameName.png");
    mNameSprite->setScale((visibleSize.width/2)/mNameSprite->getContentSize().width);
    mNameSprite->setAnchorPoint(Vec2(0.5,1));
    mNameSprite->setPosition(Vec2((origin.x +visibleSize.width)/2,origin.y + visibleSize.height - 50));
    addChild(mNameSprite);
    
    auto mRaceButton = MenuItemImage::create("RaceNormal.png","RaceSelected.png",CC_CALLBACK_1(MainMenuScene::menuPlayCallback,this));

    mRaceButton->setAnchorPoint(Vec2(0.5,0.5));
    mRaceButton->setScale((visibleSize.width/5)/mRaceButton->getNormalImage()->getContentSize().width);
    Vec2 tRaceButtonPos = Vec2((origin.x +visibleSize.width)/2,(origin.y + visibleSize.height)/2 + mRaceButton->getNormalImage()->getContentSize().height/3);
    mRaceButton->setPosition(tRaceButtonPos);
    
    
    
    auto mMapButton = MenuItemImage::create("MapNormal.png","MapSelected.png",CC_CALLBACK_1(MainMenuScene::menuMakeMapCallback,this));
    mMapButton->setAnchorPoint(Vec2(0.5,0.5));
    mMapButton->setScale((visibleSize.width/5)/mMapButton->getNormalImage()->getContentSize().width);
    Vec2 tMapButtonPos = Vec2((origin.x +visibleSize.width)/2,(origin.y + visibleSize.height)/2 - mMapButton->getNormalImage()->getContentSize().height/3);
    mMapButton->setPosition(tMapButtonPos);
    
    
    auto tRatingButton = MenuItemImage::create("RatingNormal.png","RatingSelected.png",  CC_CALLBACK_1(MainMenuScene::menuRatingCallback, this));
    tRatingButton->setAnchorPoint(Vec2(0.5,1));
    tRatingButton->setScale((visibleSize.width/12)/tRatingButton->getNormalImage()->getContentSize().width);
    tRatingButton->setPosition((origin.x +visibleSize.width)/2,mMapButton->getPosition().y - (mMapButton->getNormalImage()->getContentSize().height)/2);
    
    auto mSettingButton = MenuItemImage::create("SettingNormal.png","SettingSelected.png",CC_CALLBACK_1(MainMenuScene::menuSettingCallback,this));
    mSettingButton->setScale((visibleSize.width/12)/mSettingButton->getNormalImage()->getContentSize().width);
    mSettingButton->setAnchorPoint(Vec2(0.5,1));
    Vec2 tSettingButtonPos = Vec2((origin.x +visibleSize.width)/4, tRatingButton->getPosition().y);
    mSettingButton->setPosition(tSettingButtonPos);
    
    auto tShopButton = MenuItemImage::create("ShopNormal.png","ShopSelected.png",  CC_CALLBACK_1(MainMenuScene::menuShopCallback, this));
    tShopButton->setAnchorPoint(Vec2(0.5,1));
    tShopButton->setScale(visibleSize.width/12/tShopButton->getNormalImage()->getContentSize().width);
    tShopButton->setPosition((origin.x +visibleSize.width)/4*3,tRatingButton->getPosition().y);
    
    cocos2d::Vector<MenuItem*> items;
    items.pushBack(mRaceButton);
    items.pushBack(mMapButton);
    items.pushBack(mSettingButton);
    items.pushBack(tShopButton);
    items.pushBack(tRatingButton);
    
    auto menu = Menu::createWithArray(items);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    
    
    
    TableView* tableView = TableView::create(this, Size(300,400));

    tableView->setDirection(cocos2d::extension::ScrollView::Direction::VERTICAL);

    tableView->setPosition(Vec2(0,visibleSize.height/3));

    tableView->setDelegate(this);

    tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);

    this->addChild(tableView);

    tableView->reloadData();
    
}

void MainMenuScene::menuPlayCallback(cocos2d::Ref *pSender)
{
    auto gameScene = MainGameScene::createScene();
    Director::getInstance()->replaceScene(gameScene);
}

void MainMenuScene::menuMakeMapCallback(cocos2d::Ref *pSender)
{
    auto mapMakingScene = MapMakingScene::createScene();
    Director::getInstance()->replaceScene(mapMakingScene);
}

void MainMenuScene::menuRatingCallback(cocos2d::Ref *pSender)
{
    CCLOG("Rating");
}

void MainMenuScene::menuShopCallback(cocos2d::Ref *pSender)
{
    auto shopScene = ShopScene::createScene();
    Director::getInstance()->replaceScene(shopScene);
}

void MainMenuScene::menuSettingCallback(cocos2d::Ref *pSender)
{
    CCLOG("Setting");
}

void MainMenuScene::menuExitCallback(cocos2d::Ref* pSender){
	Director::getInstance()->end();
}


TableViewCell* MainMenuScene::tableCellAtIndex(TableView *table, ssize_t idx) {
    CC_UNUSED_PARAM(table);
    
    auto string = String::createWithFormat("%zd", idx);
    

    TableViewCell *cell = table->dequeueCell();
    
    if (!cell) {

        cell = new TableViewCell();

        cell->autorelease();

        auto sprite = Sprite::create("CloseNormal.png");

        sprite->setAnchorPoint(Vec2::ZERO);

        sprite->setPosition(Vec2(0,0));

        cell->addChild(sprite);
        

        LabelTTF *label = LabelTTF::create(string->getCString(), "Helvetica", 20.0);

        label->setPosition(Vec2::ZERO);

        label->setAnchorPoint(Vec2::ZERO);

        label->setTag(123);

        cell->addChild(label);
    }
    else
    {
        LabelTTF *label = (LabelTTF*)cell->getChildByTag(123);

        label->setString(string->getCString());
    }
    return cell;
}

ssize_t MainMenuScene::numberOfCellsInTableView(TableView *table) {
    CC_UNUSED_PARAM(table);
    
    return 20;
}

Size MainMenuScene::tableCellSizeForIndex(TableView *table, ssize_t idx) {
    CC_UNUSED_PARAM(table);
    
    return Size(100, 100);
}
