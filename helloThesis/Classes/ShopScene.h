//
//  ShopScene.h
//  GameRun
//
//  Created by TFLAT iOS Developer on 10/28/15.
//
//

#ifndef __GameRun__ShopScene__
#define __GameRun__ShopScene__
#include "cocos2d.h"
#include <stdio.h>
#include "ui/CocosGUI.h"

using namespace cocos2d::ui;
using namespace std;

USING_NS_CC;

class ShopScene : public Layer
{
private:

    vector<vector<string>> mMapNameItem;
public:
    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;
    
    MenuItemImage *mBackButton;
    MenuItemImage *mBuyButton;
    
    ListView *mListVertical;
    ListView *mListButtonChild;
    ListView *mListButonRoot;
    
    static Scene* createScene();
    virtual bool init();
    void initButton();
    
    void initListVertical();
    void initListRoot();
    void initListChild();
    
    void selectedItemVerticalListEvent(Ref *sender, ui::ListView::EventType type);
    void selectedItemRootListEvent(Ref *sender, ui::ListView::EventType type);
    void selectedItemChildListEvent(Ref *sender, ui::ListView::EventType type);
    
    void menuBackCallback(cocos2d::Ref* pSender);
    void menuBuyItemCallback(cocos2d::Ref* pSender);
    
    string getNameWithNumber(int number);
    CREATE_FUNC(ShopScene);
};
#endif /* defined(__GameRun__ShopScene__) */
