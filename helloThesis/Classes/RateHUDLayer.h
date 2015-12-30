//
//  RateHUDLayer.h
//  MyRun
//
//  Created by Thien Banh on 12/29/15.
//
//

#ifndef RateHUDLayer_h
#define RateHUDLayer_h

#include "cocos2d.h"
#include "GameConfig.h"
#include "Utility.h"
#include "HUDLayer.h"

class RateHUDLayerDelegate
{
public:
    /**
     * @js NA
     * @lua NA
     */
    virtual ~RateHUDLayerDelegate() {}
    /**
     * @js NA
     * @lua NA
     */
    virtual void exitBack() {};
    virtual void ratePress(int Number) {};
};

class RateHUDLayer : public HUDLayer
{
private:
    RateHUDLayerDelegate *mDelegate;
    MenuItemImage *mStar1Button;
    MenuItemImage *mStar2Button;
    MenuItemImage *mStar3Button;
    
    void menuStar1Callback();
    void menuStar2Callback();
    void menuStar3Callback();
    
    void menuReplayCallback();
    void menuNextCallback();
    void menuBackCallback();
    bool init(float x, float y, float time);
public:
    RateHUDLayer(Layer* parent, float time);
    ~RateHUDLayer();
    void setDelegate(RateHUDLayerDelegate* pDelegate) { mDelegate = pDelegate; }
    //touches event
    //void onTouchesBegan(const std::vector<Touch*>& touches, Event  *event);
    //void onTouchesMoved(const std::vector<Touch*>& touches, Event  *event);
    //void onTouchesEnded(const std::vector<Touch*>& touches, Event  *event);
    //void onTouchesCancelled(const std::vector<Touch*>& touches, cocos2d::Event  *event);
    
    //CC_SYNTHESIZE(Runner*, mRunner, Runner);
};


#endif /* RateHUDLayer_h */
