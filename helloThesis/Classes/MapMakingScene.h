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
    string mCurrentName;
    
public:
    std::map< std::string, std::vector<std::string> > mMapItem {
        {"castle.png", {"signExit.png", "castleCenter.png","castleCliffLeft.png","castleCliffLeftAlt.png","castleCliffRight.png","castleCliffRightAlt.png","castleHalf.png"}},
        {"boxItem.png", {"signExit.png", "boxCoin_disabled.png","boxCoin.png","boxCoinAlt.png","boxEmpty.png","boxExplosive.png","boxWarning.png"}},
        {"fence.png", {"signExit.png", "boxCoin_disabled.png","boxCoin.png","boxCoinAlt.png","boxEmpty.png","boxExplosive.png","boxWarning.png"}},
        {"signRight.png", {"signExit.png", "boxCoin_disabled.png","boxCoin.png","boxCoinAlt.png","boxEmpty.png","boxExplosive.png","boxWarning.png"}},
        {"tochLit.png", {"signExit.png", "boxCoin_disabled.png","boxCoin.png","boxCoinAlt.png","boxEmpty.png","boxExplosive.png","boxWarning.png"}},
        {"liquidWaterTop_mid.png", {"signExit.png", "boxCoin_disabled.png","boxCoin.png","boxCoinAlt.png","boxEmpty.png","boxExplosive.png","boxWarning.png"}},
        {"stoneHalf.png", {"signExit.png", "boxCoin_disabled.png","boxCoin.png","boxCoinAlt.png","boxEmpty.png","boxExplosive.png","boxWarning.png"}}
    };
   
    cocos2d::Size visibleSize;
    static cocos2d::Scene* createScene();
    ScrollView *mScrollMapView;
    ListView *mListButonView;
    string mMang2Chieu[100][100];
    virtual bool init();
    bool onTouchBegan(Touch *touch, Event *event);
    void onTouchMoved(Touch *touch, Event *event);
    
    void selectedItemListViewEvent(Ref *sender, ui::ListView::EventType type);
    
    void zoomOut(cocos2d::Ref* pSender);
    void zoomIn(cocos2d::Ref *pSender);
    CREATE_FUNC(MapMakingScene);
};

#endif