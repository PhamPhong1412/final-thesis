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
    auto background = Sprite::create("HelloWorld.png");
    background->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    background->setScale(visibleSize.width/background->getContentSize().width, visibleSize.height/background->getContentSize().height);
    this->addChild(background);
    
    initTableView();
    initButton();
    return true;
}

void RankingScene::initButton()
{
    auto mBackButton = MenuItemImage::create("ExitNormal.png", "ExitSelected.png", CC_CALLBACK_1(RankingScene::menuBackCallback, this));
    mBackButton->setAnchorPoint(Vec2(0,0));
    mBackButton->setScale((visibleSize.width/10)/mBackButton->getContentSize().width);
    mBackButton->setPosition(Vec2(origin.x,origin.y));
    addChild(mBackButton);
}

void RankingScene::initTableView()
{
    GameConfig::RANK_TABLE_WIDTH = visibleSize.width/2;
    GameConfig::RANK_TABLE_CELL_HEIGHT = 50;
    
    TableView* tableView = TableView::create(this, Size(visibleSize.width/2,visibleSize.height));
    
    tableView->setDirection(cocos2d::extension::ScrollView::Direction::VERTICAL);
    
    tableView->setPosition(Vec2(0,0));
    
    tableView->setDelegate(this);
    
    tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
    
    this->addChild(tableView);
    
    tableView->reloadData();
}

TableViewCell* RankingScene::tableCellAtIndex(TableView *table, ssize_t idx) {
    CC_UNUSED_PARAM(table);
    
    auto string = String::createWithFormat("%zd", idx);
    
    RatingTableCell *cell = (RatingTableCell*)table->dequeueCell();
    
    if (!cell) {
        
        cell = new RatingTableCell();
        
        cell->setContentSize(Size(GameConfig::RANK_TABLE_WIDTH,GameConfig::RANK_TABLE_CELL_HEIGHT));
    }
    
    cell->getNickNameLabel()->setString("thien");
    cell->getPlayCountLabel()->setString("12");
    cell->getTotalScoreLabel()->setString("3");
    
    return cell;
}

ssize_t RankingScene::numberOfCellsInTableView(TableView *table) {
    CC_UNUSED_PARAM(table);
    
    return 20;
}

Size RankingScene::tableCellSizeForIndex(TableView *table, ssize_t idx) {
    CC_UNUSED_PARAM(table);
    
    return Size(visibleSize.width/2, 50);
}

void RankingScene::tableCellTouched(TableView *table, TableViewCell *cell)
{
    CCLOG("%zi",cell->getIdx());
}

void RankingScene::menuBackCallback(cocos2d::Ref *pSender)
{
    auto mainScene = MainMenuScene::createScene();
    Director::getInstance()->replaceScene(mainScene);
}