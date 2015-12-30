//
//  RatingTableCell.h
//  GameRun
//
//  Created by Thien Banh on 11/4/15.
//
//

#ifndef __GameRun__RatingTableCell__
#define __GameRun__RatingTableCell__

#include <stdio.h>
#include "cocos2d.h"
#include "cocos-ext.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocos2d::ui;

class RatingTableCell : public TableViewCell {
public:
    RatingTableCell();
    ~RatingTableCell();
	
    CC_SYNTHESIZE(cocos2d::Sprite*, _cellBackground, CellBackground);
	CC_SYNTHESIZE(Sprite*, _lbStarSprite, StarSprite);

	CC_SYNTHESIZE(Label*, _lbIndex, IndexLabel);
    CC_SYNTHESIZE(Label*, _lbNickName, NickNameLabel);
	CC_SYNTHESIZE(Label*, _lbPlayCount, PlayCountLabel);
	CC_SYNTHESIZE(Label*, _lbTotalScore, TotalScoreLabel);
};
#endif /* defined(__GameRun__RatingTableCell__) */
