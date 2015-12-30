//
//  RatingTableCell.cpp
//  GameRun
//
//  Created by Thien Banh on 11/4/15.
//
//

#include "RatingTableCell.h"
#include "GameConfig.h"

RatingTableCell::RatingTableCell():_cellBackground(NULL), _lbNickName(NULL), _lbPlayCount(NULL), _lbTotalScore(NULL) {
    
    const float gapLeft = 50.0f;
    const float gapRight = 10.0f;
    
    const float fontSize = 15.0f;
    
    const float widthPlayCount  = 40.0f;
    const float widthTotalScore = 80.0f;
    const float widthNickName   = (widthPlayCount + widthTotalScore) - (gapLeft + gapRight);

    
    
    auto *sprite = Sprite::create("Cell.png");
    cocos2d::Size spriteSize = sprite->getContentSize();
    sprite->setAnchorPoint(Vec2(0,0));
    sprite->setPosition( Vec2(0,0) );
    sprite->setScale(GameConfig::RANK_TABLE_WIDTH/spriteSize.width,GameConfig::RANK_TABLE_CELL_HEIGHT/spriteSize.height);
    this->addChild(sprite);

	_lbStarSprite = Sprite::create("Star3.png");
	_lbStarSprite->setAnchorPoint(Vec2(1, 0.5));
	_lbStarSprite->setPosition(Vec2(GameConfig::RANK_TABLE_WIDTH - 10, GameConfig::RANK_TABLE_CELL_HEIGHT / 2));
	_lbStarSprite->setScale(0.5);
	this->addChild(_lbStarSprite);

	// Text : Index
	_lbIndex = Label::createWithTTF("", "arial.ttf", fontSize);
	_lbIndex->setAnchorPoint(Vec2(0, 0.5));
	_lbIndex->setColor(Color3B::BLACK);
	_lbIndex->setPosition(Vec2(20, GameConfig::RANK_TABLE_CELL_HEIGHT / 2 ));
	this->addChild(_lbIndex);

    // Text : NickName
    
	_lbNickName = Label::createWithTTF("", "arial.ttf", fontSize);
	_lbNickName->setAnchorPoint(Vec2(0, 0.5));
	_lbNickName->setColor(Color3B::BLACK);
	_lbNickName->setPosition(Vec2(gapLeft, GameConfig::RANK_TABLE_CELL_HEIGHT / 2 + 25));
    this->addChild(_lbNickName);
    
    // Text : PlayCount
	_lbPlayCount = Label::createWithTTF("", "arial.ttf", fontSize);
	_lbPlayCount->setAnchorPoint(Vec2(0, 0.5));
	_lbPlayCount->setColor(Color3B::BLACK);
	_lbPlayCount->setPosition(Vec2(gapLeft , GameConfig::RANK_TABLE_CELL_HEIGHT / 2));
    this->addChild(_lbPlayCount);
    
    // Text : TotalScore
	_lbTotalScore = Label::createWithTTF("", "arial.ttf", fontSize);
	_lbTotalScore->setAnchorPoint(Vec2(0, 0.5)); 
	_lbTotalScore->setColor(Color3B::BLACK);
	_lbTotalScore->setPosition(Vec2(gapLeft, GameConfig::RANK_TABLE_CELL_HEIGHT / 2 - 25));
    this->addChild(_lbTotalScore);
}

RatingTableCell::~RatingTableCell() {}