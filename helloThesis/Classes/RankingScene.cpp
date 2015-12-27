//
//  RankingScene.cpp
//  GameRun
//
//  Created by Thien Banh on 11/16/15.
//
//

#include "RankingScene.h"
Scene* RankingScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = RankingScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool RankingScene::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Layer::init())
    {
        return false;
    }
    
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
    auto background = Sprite::create("bg3.png");
    background->setPosition(Vec2(origin.x + visibleSize.width / 2,origin.y + visibleSize.height / 2));
    background->setScale(visibleSize.width/background->getContentSize().width, visibleSize.height/background->getContentSize().height);
    this->addChild(background);

	mNewButton = MenuItemImage::create("RankLeftButton2.png", "RankLeftButton1.png", CC_CALLBACK_1(RankingScene::newPress, this));
	mNewButton->setAnchorPoint(Vec2(1, 1));
	mNewButton->setScale(0.7);
	mNewButton->setPosition(Vec2(origin.x + visibleSize.width / 2 - 5, origin.y + visibleSize.height - 70));

	mTopRateButton = MenuItemImage::create("RankRightButton2.png", "RankRightButton1.png", CC_CALLBACK_1(RankingScene::topRatePress, this));
	mTopRateButton->setScale(0.7);
	mTopRateButton->setAnchorPoint(Vec2(0, 1));
	mTopRateButton->setPosition(Vec2(origin.x + visibleSize.width / 2 - 5, origin.y + visibleSize.height - 70));

	mTopRateButton->unselected();
	mNewButton->selected();

	cocos2d::Vector<MenuItem*> items;
	items.pushBack(mTopRateButton);
	items.pushBack(mNewButton);
	
	auto menu = Menu::createWithArray(items);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

    auto RankTableBG = Sprite::create("Rank.png");
    RankTableBG->setPosition(Vec2(origin.x + visibleSize.width / 2,origin.y + visibleSize.height / 2));
    RankTableBG->setScale((visibleSize.width/2)/RankTableBG->getContentSize().width, visibleSize.height/RankTableBG->getContentSize().height);
    this->addChild(RankTableBG);

	auto backgroundButton = Sprite::create("RankBG.png");
	backgroundButton->setAnchorPoint(Vec2(0.5, 1));
	backgroundButton->setPosition(Vec2(origin.x + visibleSize.width / 2 - 5, origin.y + visibleSize.height - 67));
	backgroundButton->setScale(0.7);
	this->addChild(backgroundButton);

	auto button1Text = Label::createWithTTF("NEW", "Marker Felt.ttf", 30);
	button1Text->setAnchorPoint(Vec2(1, 1));
	// position the label on the center of the screen
	button1Text->setPosition(Vec2(origin.x + visibleSize.width / 2 - 40, origin.y + visibleSize.height - 75));
	button1Text->setTextColor(Color4B(255, 255, 255, 255));
	button1Text->setZOrder(2);
	this->addChild(button1Text);

	auto button2Text = Label::createWithTTF("TOP", "Marker Felt.ttf", 30);
	button2Text->setAnchorPoint(Vec2(0, 1));
	// position the label on the center of the screen
	button2Text->setPosition(Vec2(origin.x + visibleSize.width / 2 + 35, origin.y + visibleSize.height - 75));
	button2Text->setTextColor(Color4B(255, 255, 255, 255));
	button2Text->setZOrder(2);
	this->addChild(button2Text);

    initTableView();
    initButton();
    return true;
}

void RankingScene::newPress(cocos2d::Ref *pSender)
{
	if (mNewButton->isSelected())
	{

	}
	else
	{
		mNewButton->selected();
		mTopRateButton->unselected();
	}
	
	CCLOG("new");
}

void RankingScene::topRatePress(cocos2d::Ref *pSender)
{
	if (mTopRateButton->isSelected())
	{

	}
	else
	{
		mTopRateButton->selected();
		mNewButton->unselected();
	}
	
	CCLOG("top");
}

void RankingScene::initButton()
{
	cocos2d::Vector<MenuItem*> items;
	auto mBackButton = MenuItemImage::create("ExitNormal.png", "ExitSelected.png", CC_CALLBACK_0(RankingScene::menuBackCallback, this));
	mBackButton->setAnchorPoint(Vec2(0, 0));
	mBackButton->setScale(BUTTON_SIZE / mBackButton->getContentSize().width);
	mBackButton->setPosition(origin.x , origin.y );
	items.pushBack(mBackButton);
	auto menu = Menu::createWithArray(items);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);
}

void RankingScene::initTableView()
{
    GameConfig::RANK_TABLE_WIDTH = visibleSize.width/2 - 50;
    GameConfig::RANK_TABLE_CELL_HEIGHT = DESIGN_SCREEN_HEIGHT/5;
    
    TableView* tableView = TableView::create(this, Size(GameConfig::RANK_TABLE_WIDTH,visibleSize.height - 150));
    
    tableView->setDirection(cocos2d::extension::ScrollView::Direction::VERTICAL);
    
	tableView->setPosition(Vec2(origin.x + DESIGN_SCREEN_WIDTH/4 + 25, origin.y + 25));
    
    tableView->setDelegate(this);
    
    tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
    
    this->addChild(tableView);
    
    tableView->reloadData();
}

TableViewCell* RankingScene::tableCellAtIndex(TableView *table, ssize_t idx) {
    CC_UNUSED_PARAM(table);
    
    auto string = cocos2d::StringUtils::format("%i", idx);
    
    RatingTableCell *cell = (RatingTableCell*)table->dequeueCell();
    
    if (!cell) {
        
        cell = new RatingTableCell();
        
        cell->setContentSize(Size(GameConfig::RANK_TABLE_WIDTH,GameConfig::RANK_TABLE_CELL_HEIGHT));
    }
	cell->getIndexLabel()->setString(string);
    cell->getNickNameLabel()->setString("Creater: Thien");
    cell->getPlayCountLabel()->setString("Played: 56");
    cell->getTotalScoreLabel()->setString("Best time: 1m30s");
    
    return cell;
}

ssize_t RankingScene::numberOfCellsInTableView(TableView *table) {
    CC_UNUSED_PARAM(table);
    
    return 20;
}

Size RankingScene::tableCellSizeForIndex(TableView *table, ssize_t idx) {
    CC_UNUSED_PARAM(table);
    
	return Size(GameConfig::RANK_TABLE_WIDTH, GameConfig::RANK_TABLE_CELL_HEIGHT);
}

void RankingScene::tableCellTouched(TableView *table, TableViewCell *cell)
{
    CCLOG("%zd",cell->getIdx());
	std::string test = DBContext::get("map_test");
	auto gameScene = MainGameScene::createScene(false,test);
	Director::getInstance()->replaceScene(gameScene);
}

void RankingScene::menuBackCallback()
{
    auto mainScene = MainMenuScene::createScene();
    Director::getInstance()->replaceScene(mainScene);
}