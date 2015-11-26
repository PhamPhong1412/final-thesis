#ifndef _MAP_MAKING_SCENE_H_
#define _MAP_MAKING_SCENE_H_


#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include <map>
#include <list>
#include "DBContext.h"
#include "MainGameScene.h"
#include "WidthHeightChooseHUD.h"

using namespace cocos2d::ui;
using namespace std;
USING_NS_CC;

class MapMakingScene : public Layer, public WidthHeightChooseDelegate
{
private:
    bool isChooseInfo;
    bool mCheckRootItem;
    Sprite *map;
    int tile_size;
    float mScaleValue;
    int mCurrentRootItem;
    int numberTileWidth;
    int numberTileHeight;
    string mCurrentNameChild;
    string mMapSave;
    
    Menu *menu;
    MenuItemImage *mMoveButton;
    MenuItemImage *mInsertButton;
    MenuItemImage *mRemoveButton;
    MenuItemImage *mChangeSizeButton;
    
public:
    
    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;
    static cocos2d::Scene* createScene();
    
    vector<vector<string>> mMapNameItem;
    vector<string> tVectorNameChildItem;
    
    vector<vector<string>> mVector2Chieu;

    ui::ScrollView *mScrollMapView;
    
    ListView *mListButtonChild;
    ListView *mListButonRoot;
    virtual bool init();
    
    virtual void exitBack(int width, int height);
    
    bool onTouchBegan(Touch *touch, Event *event);
    void onTouchMoved(Touch *touch, Event *event);
    void onTouchEnded(Touch *touch, Event *event);
    
    void selectedItemRootListEvent(Ref *sender, ui::ListView::EventType type);
    void selectedItemChildListEvent(Ref *sender, ui::ListView::EventType type);
    string getNameWithNumber(int number);
    
    void saveMap(cocos2d::Ref* pSender);
    void startMove(cocos2d::Ref *pSender);
    void startRemove(cocos2d::Ref* pSender);
    void startInsert(cocos2d::Ref *pSender);
    
    // LOCAL FUNCION
	void initCreateMapView(bool withBackground);
    void initListItem();
    void initButton();
    void initScrollMapView();
    void initListChild();
    void initListRoot();
    
    CREATE_FUNC(MapMakingScene);
};

#endif