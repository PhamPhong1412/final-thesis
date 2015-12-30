//
//  RankingScene.h
//  GameRun
//
//  Created by Thien Banh on 11/16/15.
//
//

#ifndef __GameRun__RankingScene__
#define __GameRun__RankingScene__

#include <stdio.h>
#include "cocos2d.h"
#include "cocos-ext.h"
#include "GameConfig.h"
#include "RatingTableCell.h"
#include "MainMenuScene.h"
#include "HttpServices.h"

USING_NS_CC;
USING_NS_CC_EXT;

class RankingScene : public Layer,public cocos2d::extension::TableViewDelegate,cocos2d::extension::TableViewDataSource, public HttpServicesDelegate
{
private:
	MenuItemImage *mNewButton;
	MenuItemImage *mTopRateButton;

	std::vector<HttpShortMapInfo> listMap;
    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;
	TableView* tableView;

	bool mIsStopLoad;
	int currentSize;
	int pageSize;
public:
    
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    
    void initTableView();
    void initButton();
    
	void newPress(cocos2d::Ref *pSender);
	void topRatePress(cocos2d::Ref *pSender);
	void menuBackCallback();
    
    
    
    virtual TableViewCell* tableCellAtIndex(TableView *table, ssize_t idx);
    virtual ssize_t numberOfCellsInTableView(TableView *table);
    virtual cocos2d::Size tableCellSizeForIndex(TableView *table, ssize_t idx) override;
    virtual void tableCellTouched(TableView *table, TableViewCell *cell);
    
    virtual void scrollViewDidScroll(cocos2d::extension::ScrollView *view) {};

	virtual void getMapRatingRank(std::vector<HttpShortMapInfo> result);
	virtual void getMapUploadTimeRank(std::vector<HttpShortMapInfo> result);
	virtual void getMapInfo(HttpShortMapInfo result);

	void loadNew();
	void loadTop();
    CREATE_FUNC(RankingScene);
};
#endif /* defined(__GameRun__RankingScene__) */
