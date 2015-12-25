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
    
    const float gapLeft = 10.0f;
    const float gapRight = 10.0f;
    
    const float fontSize = 20.0f;
    
    const float widthPlayCount  = 40.0f;
    const float widthTotalScore = 80.0f;
    const float widthNickName   = (widthPlayCount + widthTotalScore) - (gapLeft + gapRight);
    
    const float posNickName = gapLeft;
    const float posPlayCount = posNickName + widthNickName;
    const float posTotalScore = posPlayCount + widthPlayCount;
    
    
    auto *sprite = Sprite::create("Cell.png");
    cocos2d::Size spriteSize = sprite->getContentSize();
    sprite->setAnchorPoint(Vec2(0,0));
    sprite->setPosition( Vec2(0,0) );
    sprite->setScale(GameConfig::RANK_TABLE_WIDTH/spriteSize.width,GameConfig::RANK_TABLE_CELL_HEIGHT/spriteSize.height);
    this->addChild(sprite);
    
    // Text : NickName
    
    _lbNickName = Text::create("", "arial.ttf", fontSize);

    _lbNickName->setColor( Color3B::BLUE );
    _lbNickName->setPosition( Vec2(posNickName + widthNickName/2, GameConfig::RANK_TABLE_CELL_HEIGHT/2) );
    this->addChild(_lbNickName);
    
    // Text : PlayCount
    _lbPlayCount = Text::create("", "arial.ttf", fontSize);
    
    _lbPlayCount->setColor( Color3B::BLUE );
    _lbPlayCount->setPosition( Vec2(posPlayCount + widthPlayCount/2, GameConfig::RANK_TABLE_CELL_HEIGHT/2) );
    this->addChild(_lbPlayCount);
    
    // Text : TotalScore
    _lbTotalScore = Text::create("", "arial.ttf", fontSize);
   
    _lbTotalScore->setColor( Color3B::BLUE );
    _lbTotalScore->setPosition( Vec2(posTotalScore + widthTotalScore/2, GameConfig::RANK_TABLE_CELL_HEIGHT/2) );
    this->addChild(_lbTotalScore);
}

RatingTableCell::~RatingTableCell() {}