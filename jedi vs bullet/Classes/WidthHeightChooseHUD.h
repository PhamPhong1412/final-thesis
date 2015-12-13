//
//  WidthHeightChooseHUD.h
//  GameRun
//
//  Created by Thien Banh on 11/14/15.
//
//

#ifndef __GameRun__WidthHeightChooseHUD__
#define __GameRun__WidthHeightChooseHUD__

#include <stdio.h>
#include "HUDLayer.h"
#include "ui/CocosGUI.h"


class WidthHeightChooseHUD;

class WidthHeightChooseDelegate
{
public:
    /**
     * @js NA
     * @lua NA
     */
    virtual ~WidthHeightChooseDelegate() {}
    /**
     * @js NA
     * @lua NA
     */
    virtual void exitBack() {};
    
};

class WidthHeightChooseHUD : public HUDLayer
{
private:
    WidthHeightChooseDelegate *mDelegate;
    void menuBackCallback();
	void menuShareCallback();
	bool init();
public:
	WidthHeightChooseHUD(Layer* parent, bool canExit);
    ~WidthHeightChooseHUD();
    
    void setDelegate(WidthHeightChooseDelegate* pDelegate) { mDelegate = pDelegate; }
    
    
    //CC_SYNTHESIZE(Runner*, mRunner, Runner);
};
#endif /* defined(__GameRun__WidthHeightChooseHUD__) */
