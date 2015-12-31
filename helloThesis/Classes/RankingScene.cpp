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
	pageSize = 5;
	currentSize = 0;
	mIsStopLoad = false;

	std::vector<HttpRequestParameter> resData{ HttpRequestParameter(phoneKey, "test"), HttpRequestParameter("start", StringUtils::format("%i", currentSize)), HttpRequestParameter("end", StringUtils::format("%i", currentSize + pageSize))};
	HttpServices::inst->sendRequest(this, resData, HttpRequestMethod::GET_MAP_UPLOAD_TIME_RANK);
	HttpServices::inst->setDelegate(this);

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
	menu->setTag(TAG_BUTTON_LAYER);
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
		pageSize = 5;
		currentSize = 0;
		mIsStopLoad = false;
		listMap._Pop_back_n(listMap.size());
		mNewButton->selected();
		mTopRateButton->unselected();
		loadNew();
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
		pageSize = 5;
		currentSize = 0;
		mIsStopLoad = false;
		listMap._Pop_back_n(listMap.size());
		mTopRateButton->selected();
		mNewButton->unselected();
		loadTop();
	}

	CCLOG("top");
}

void RankingScene::loadNew()
{
	if (!mIsStopLoad)
	{
		std::vector<HttpRequestParameter> resData{ HttpRequestParameter(phoneKey, "test"), HttpRequestParameter("start", StringUtils::format("%i", currentSize)), HttpRequestParameter("end", StringUtils::format("%i", currentSize + pageSize)) };
		HttpServices::inst->sendRequest(this, resData, HttpRequestMethod::GET_MAP_UPLOAD_TIME_RANK);
	}
	
}

void RankingScene::loadTop()
{
	if (!mIsStopLoad)
	{
		std::vector<HttpRequestParameter> resData{ HttpRequestParameter(phoneKey, "test"), HttpRequestParameter("start", StringUtils::format("%i", currentSize)), HttpRequestParameter("end", StringUtils::format("%i", currentSize + pageSize)) };
		HttpServices::inst->sendRequest(this, resData, HttpRequestMethod::GET_MAP_RATING_RANK);
	}
}

void RankingScene::getMapUploadTimeRank(std::vector<HttpShortMapInfo> result)
{
	if (result.size() < pageSize)
	{
		mIsStopLoad = true;
	}
	bool isFirst = false;

	if (listMap.size() == 0)
	{
		isFirst = true;
	}
	currentSize += result.size();
	
	for (int i = 0; i < result.size(); i++)
	{
		listMap.push_back(result[i]);
	}

	Vec2 pos = tableView->minContainerOffset();
	tableView->reloadData();
	
	
	if (!isFirst)
	{
		tableView->getContainer()->setPosition(pos);
	}

}

void RankingScene::getMapRatingRank(std::vector<HttpShortMapInfo> result)
{
	if (result.size() < pageSize)
	{
		mIsStopLoad = true;
	}

	currentSize += result.size();
	for (int i = 0; i < result.size(); i++)
	{
		listMap.push_back(result[i]);
	}
	Point pos = tableView->getContainer()->getPosition();
	tableView->getContainer()->setPosition(pos);
	tableView->reloadData();

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
    
    tableView = TableView::create(this, Size(GameConfig::RANK_TABLE_WIDTH,visibleSize.height - 150));
    
    tableView->setDirection(cocos2d::extension::ScrollView::Direction::VERTICAL);
    
	tableView->setPosition(Vec2(origin.x + DESIGN_SCREEN_WIDTH/4 + 25, origin.y + 25));
    
    tableView->setDelegate(this);
    
    tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
    
    this->addChild(tableView);
    
    tableView->reloadData();
}

TableViewCell* RankingScene::tableCellAtIndex(TableView *table, ssize_t idx) {
    CC_UNUSED_PARAM(table);
    
    auto string = cocos2d::StringUtils::format("%i", idx+1);
    
    RatingTableCell *cell = (RatingTableCell*)table->dequeueCell();
    
    if (!cell) {
        
        cell = new RatingTableCell();
        
        cell->setContentSize(Size(GameConfig::RANK_TABLE_WIDTH,GameConfig::RANK_TABLE_CELL_HEIGHT));
    }
	HttpShortMapInfo mapInfo = listMap[idx];
	/*std::string mid;
	std::string creatorID;
	std::string rating;
	std::string data;
	std::string uploadTime;
	std::string rateCounter;
	std::string playTime;*/

	std::string year = mapInfo.uploadTime.substr(0, 4);
	std::string mounth = mapInfo.uploadTime.substr(4,2);
	std::string day = mapInfo.uploadTime.substr(6, 2);
	if (mNewButton->isSelected())
	{
		std::string text = "Uploaded: " +day+"/" + mounth +"/"+year;
		cell->getPlayCountLabel()->setString(text);
	}
	else
	{
		cell->getPlayCountLabel()->setString("Rated: " + mapInfo.rateCounter);
	}

	cell->getStarSprite()->setVisible(true);
	if (stoi(mapInfo.rating) == 1)
	{
		cell->getStarSprite()->setTexture("Star.png");
	}
	else if (stoi(mapInfo.rating) == 2)
	{
		cell->getStarSprite()->setTexture("Star2.png");
	}
	else if (stoi(mapInfo.rating) >= 3)
	{
		cell->getStarSprite()->setTexture("Star3.png");
	}
	else if (stoi(mapInfo.rating) == 0)
	{
		cell->getStarSprite()->setVisible(false);
	}
	
	cell->getIndexLabel()->setString(string);
    cell->getNickNameLabel()->setString("Creater: Thien");
    
	float playtime = stof(mapInfo.playTime) / 1000;
    cell->getTotalScoreLabel()->setString(StringUtils::format("Best: %.2fs" , playtime));
    
	if (idx == listMap.size() - 1)
	{
		if (mNewButton->isSelected())
		{
			loadNew();
		}
		else
		{
			loadTop();
		}
	}
    return cell;
}

ssize_t RankingScene::numberOfCellsInTableView(TableView *table) {
    CC_UNUSED_PARAM(table);

	return listMap.size();
}

Size RankingScene::tableCellSizeForIndex(TableView *table, ssize_t idx) {
    CC_UNUSED_PARAM(table);
    
	return Size(GameConfig::RANK_TABLE_WIDTH, GameConfig::RANK_TABLE_CELL_HEIGHT);
}

void RankingScene::tableCellTouched(TableView *table, TableViewCell *cell)
{
    CCLOG("%zd",cell->getIdx());
	HttpShortMapInfo mapInfo = listMap[cell->getIdx()];

	std::vector<HttpRequestParameter> resData{ HttpRequestParameter(phoneKey, "test"), HttpRequestParameter("mid", mapInfo.mid) };
	HttpServices::inst->sendRequest(this, resData, HttpRequestMethod::GET_MAP_INFO);
	/*HttpServices::inst->setDelegate(this);*/
}

void RankingScene::getMapInfo(HttpShortMapInfo result)
{
	std::string test = result.data;
	auto gameScene = MainGameScene::createScene(false, test, result);
	Director::getInstance()->replaceScene(gameScene);
}

void RankingScene::menuBackCallback()
{
    auto mainScene = MainMenuScene::createScene();
    Director::getInstance()->replaceScene(mainScene);
}