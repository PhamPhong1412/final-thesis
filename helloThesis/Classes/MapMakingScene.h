#ifndef _MAP_MAKING_SCENE_H_
#define _MAP_MAKING_SCENE_H_


#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include <map>

using namespace cocos2d::ui;
using namespace std;
USING_NS_CC;

class MapMakingScene : public Layer
{
private:
    bool mCheckRootItem;
    Sprite *map;
    int tile_size;
    float mScaleValue;
    int mCurrentRootItem;
    string mCurrentNameChild;
    string mCurrentNameRoot;
public:
    
    std::map< std::string, std::vector<std::string> > mMapItem {
        {"castle.png", {"signExit.png", "castle.png","castleCenter.png","castleCliffLeft.png","castleCliffLeftAlt.png","castleCliffRight.png","castleCliffRightAlt.png","castleHalf.png"}},
        {"boxItem.png", {"signExit.png", "boxItem.png","boxCoin_disabled.png","boxCoin.png","boxCoinAlt.png","boxEmpty.png","boxExplosive.png","boxWarning.png","lock_blue.png","lock_green.png","lock_red.png","lock_yellow.png"}},
        {"fence.png", {"signExit.png", "fence.png","door_closedMid.png","door_closedTop.png","fenceBroken.png","door_openTop.png","door_openMid.png","ladder_top.png","ladder_mid.png"}},
        {"signRight.png", {"signExit.png", "signRight.png","signLeft.png","signRight.png","sign.png"}},
        {"tochLit.png", {"signExit.png", "tochLit.png","torch.png","tochLit2.png","window.png"}},
        {"liquidWaterTop_mid.png", {"signExit.png", "liquidWaterTop_mid.png","liquidWaterTop.png","liquidWater.png","liquidLavaTop.png","liquidLavaTop_mid.png","liquidLava.png"}},
        {"stoneHalf.png", {"signExit.png", "stoneHalf.png","stoneHalfLeft.png","stoneHalfMid.png","stoneHalfRight.png","stoneHillLeft2.png","stoneHillRight2.png","stoneMid.png"}}
    };
   
    cocos2d::Size visibleSize;
    static cocos2d::Scene* createScene();
    
    std::vector<std::string> tVectorNameChildItem;
    
    ScrollView *mScrollMapView;
    ListView *mListButtonChild;
    ListView *mListButonRoot;
    string mMang2Chieu[100][100];
    virtual bool init();
    bool onTouchBegan(Touch *touch, Event *event);
    void onTouchMoved(Touch *touch, Event *event);
    
    void selectedItemRootListEvent(Ref *sender, ui::ListView::EventType type);
    void selectedItemChildListEvent(Ref *sender, ui::ListView::EventType type);
    string getNameWithNumber(int number);
    void zoomOut(cocos2d::Ref* pSender);
    void zoomIn(cocos2d::Ref *pSender);
    CREATE_FUNC(MapMakingScene);
};

#endif