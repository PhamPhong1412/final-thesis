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
    const float widthNickName   = GameConfig::RANK_TABLE_WIDTH - (widthPlayCount + widthTotalScore) - (gapLeft + gapRight);
    
    const float posNickName = gapLeft;
    const float posPlayCount = posNickName + widthNickName;
    const float posTotalScore = posPlayCount + widthPlayCount;
    
    // Background
    
//    Sprite *sprite = Sprite::create("HelloWorld.png");
//    cocos2d::Size spriteSize = sprite->getContentSize();
//    sprite->setPosition( Vec2(spriteSize.width/2, spriteSize.height/2) );
//    sprite->setScale(0.5);
//    this->addChild(sprite);
    
    // Text : NickName
    
    _lbNickName = Text::create("", "arial.ttf", fontSize);

    _lbNickName->setColor( Color3B::RED );
    _lbNickName->setPosition( Vec2(posNickName + widthNickName/2, GameConfig::RANK_TABLE_CELL_HEIGHT/2) );
    this->addChild(_lbNickName);
    
    // Text : PlayCount
    _lbPlayCount = Text::create("", "arial.ttf", fontSize);
    
    _lbPlayCount->setColor( Color3B::RED );
    _lbPlayCount->setPosition( Vec2(posPlayCount + widthPlayCount/2, GameConfig::RANK_TABLE_CELL_HEIGHT/2) );
    this->addChild(_lbPlayCount);
    
    // Text : TotalScore
    _lbTotalScore = Text::create("", "arial.ttf", fontSize);
   
    _lbTotalScore->setColor( Color3B::RED );
    _lbTotalScore->setPosition( Vec2(posTotalScore + widthTotalScore/2, GameConfig::RANK_TABLE_CELL_HEIGHT/2) );
    this->addChild(_lbTotalScore);
}

RatingTableCell::~RatingTableCell() {}