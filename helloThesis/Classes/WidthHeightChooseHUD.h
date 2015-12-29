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
    virtual void exitBack(int width, int height) {};
	virtual void loadLocalMap() {};
    
};

class WidthHeightChooseHUD : public HUDLayer
{
private:
    WidthHeightChooseDelegate *mDelegate;
    void menuHideKeyboardCallback();
    void menuBackCallback();
    void menuNewCallback();
	void menuNextCallback();
	bool haveLocalMap;
	bool init(bool withBackground);
	
	MenuItemImage *mBackButton;
    MenuItemImage *mNewButton;
	MenuItemImage *mNextButton;

	Label *infoLabel;

    ui::EditBox *mWidthEditBox;
    ui::EditBox *mHeightEditBox;
public:
	WidthHeightChooseHUD(Layer* parent, bool canExit, bool withBackground);
    ~WidthHeightChooseHUD();
    
    void setDelegate(WidthHeightChooseDelegate* pDelegate) { mDelegate = pDelegate; }
    
    //void onTouchesMoved(const std::vector<Touch*>& touches, Event  *event);
    //void onTouchesEnded(const std::vector<Touch*>& touches, Event  *event);
    //void onTouchesCancelled(const std::vector<Touch*>& touches, cocos2d::Event  *event);
    
    
    //CC_SYNTHESIZE(Runner*, mRunner, Runner);
};
#endif /* defined(__GameRun__WidthHeightChooseHUD__) */
