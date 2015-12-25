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
    
    auto RankTableBG = Sprite::create("Rank.png");
    RankTableBG->setPosition(Vec2(origin.x + visibleSize.width / 2,origin.y + visibleSize.height / 2));
    RankTableBG->setScale((visibleSize.width/2)/RankTableBG->getContentSize().width, visibleSize.height/RankTableBG->getContentSize().height);
    this->addChild(RankTableBG);
    
    initTableView();
    initButton();
    return true;
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
    
    auto string = cocos2d::StringUtils::format("%zd", idx);
    
    RatingTableCell *cell = (RatingTableCell*)table->dequeueCell();
    
    if (!cell) {
        
        cell = new RatingTableCell();
        
        cell->setContentSize(Size(GameConfig::RANK_TABLE_WIDTH,GameConfig::RANK_TABLE_CELL_HEIGHT));
    }
    
    cell->getNickNameLabel()->setString("thien");
    cell->getPlayCountLabel()->setString("12");
    cell->getTotalScoreLabel()->setString(string);
    
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