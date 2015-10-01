#include "MapMakingScene.h"
enum States
{
    Move,
    Remove,
    Insert
};

States mCurrentState;
Scene* MapMakingScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MapMakingScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MapMakingScene::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Layer::init())
    {
        return false;
    }
    
    mCurrentState = Move;
    mCurrentNameChild = "boxCoinAlt.png";
    mCheckRootItem = true;
    
    visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    mScaleValue = 1.0f;
    
    vector<string> tTemp0 = {"signExit.png", "castle.png","castleCenter.png","castleCliffLeft.png","castleCliffLeftAlt.png","castleCliffRight.png","castleCliffRightAlt.png","castleHalf.png"};
    vector<string> tTemp1 = {"signExit.png", "boxItem.png","boxCoin_disabled.png","boxCoin.png","boxCoinAlt.png","boxEmpty.png","boxExplosive.png","boxWarning.png","lock_blue.png","lock_green.png","lock_red.png","lock_yellow.png"};
    vector<string> tTemp2 = {"signExit.png", "fence.png","door_closedMid.png","door_closedTop.png","fenceBroken.png","door_openTop.png","door_openMid.png","ladder_top.png","ladder_mid.png"};
    vector<string> tTemp3 = {"signExit.png", "signRight.png","signLeft.png","signRight.png","sign.png"};
    vector<string> tTemp4 = {"signExit.png", "tochLit.png","torch.png","tochLit2.png","window.png"};
    vector<string> tTemp5 = {"signExit.png", "liquidWaterTop_mid.png","liquidWaterTop.png","liquidWater.png","liquidLavaTop.png","liquidLavaTop_mid.png","liquidLava.png"};
    vector<string> tTemp6 = {"signExit.png", "stoneHalf.png","stoneHalfLeft.png","stoneHalfMid.png","stoneHalfRight.png","stoneHillLeft2.png","stoneHillRight2.png","stoneMid.png"};
    
    mMapNameItem.push_back(tTemp0);
    mMapNameItem.push_back(tTemp1);
    mMapNameItem.push_back(tTemp2);
    mMapNameItem.push_back(tTemp3);
    mMapNameItem.push_back(tTemp4);
    mMapNameItem.push_back(tTemp5);
    mMapNameItem.push_back(tTemp6);
    
    tile_size = 70;
    auto numberTileWidth = 200;
    auto numberTileHeight = 60;
    for (int i = 0; i < numberTileWidth; i++) {
        mVector2Chieu.push_back(vector<string>());
        for (int j = 0 ; j < numberTileHeight; j++) {
            mVector2Chieu[i].push_back("0");
        }
    }
    // SETUP LIST VIEW CHILD
    mListButtonChild = ui::ListView::create();
    mListButtonChild->setDirection(ui::ScrollView::Direction::VERTICAL);
    mListButtonChild->setClippingEnabled(false);
    mListButtonChild->setPosition(Vec2(0,origin.y));
    mListButtonChild->setContentSize(Size(visibleSize.width/10,visibleSize.height));
    mListButtonChild->setItemsMargin(10);
    mListButtonChild->addEventListener((ui::ListView::ccListViewCallback)CC_CALLBACK_2(MapMakingScene::selectedItemChildListEvent, this));
    mListButtonChild->setBackGroundImageScale9Enabled(true);
    mListButtonChild->setScrollBarEnabled(false);
    mListButtonChild->setBackGroundImage("bg_castle.png");
    mListButtonChild->setVisible(false);
    addChild(mListButtonChild);
    
    
    // SETUP LISTVIEW ROOT
    mListButonRoot = ui::ListView::create();
    mListButonRoot->setDirection(ui::ScrollView::Direction::VERTICAL);
    mListButonRoot->setClippingEnabled(false);
    mListButonRoot->setPosition(Vec2(0,origin.y));
    mListButonRoot->setContentSize(Size(visibleSize.width/10,visibleSize.height));
    for (int i =0 ; i<mMapNameItem.size() ; i++) {
        ui::Button *button = ui::Button::create(getNameWithNumber(i));
        mListButonRoot->pushBackCustomItem(button);
    }
    
    mListButonRoot->setItemsMargin(10);
	mListButonRoot->addEventListener((ui::ListView::ccListViewCallback)CC_CALLBACK_2(MapMakingScene::selectedItemRootListEvent, this));
    mListButonRoot->setScrollBarEnabled(false);
    mListButonRoot->setBackGroundImageScale9Enabled(true);
    mListButonRoot->setBackGroundImage("bg_castle.png");
    addChild(mListButonRoot);
    
    // SETUP SCROLL VIEW
    mScrollMapView = ui::ScrollView::create();
    mScrollMapView->setDirection(ui::ScrollView::Direction::BOTH);
    mScrollMapView->setContentSize(Size(visibleSize.width + origin.x, visibleSize.height + origin.y));
    mScrollMapView->setInnerContainerSize(Size(tile_size*numberTileWidth + visibleSize.width/10 + origin.x, tile_size*numberTileHeight + origin.y));
    mScrollMapView->setPosition(Vec2(visibleSize.width/10,origin.y));
    mScrollMapView->setScrollBarEnabled(true);
    mScrollMapView->setBackGroundImage("bg.png");
    mScrollMapView->setBackGroundImageScale9Enabled(true);
    addChild(mScrollMapView);
    
    Color4F color(0, 0, 0.5, 0.5);
    auto draw_node = DrawNode::create();
    
    for (int i = 0; i < numberTileWidth + 1; i++)
    {
        auto x = i * tile_size;
        draw_node->drawLine(Vec2(x, 0), Vec2(x, mScrollMapView->getInnerContainerSize().height), color);
    }
    for (int i = 0; i < numberTileHeight + 1; i++)
    {
        auto y = i *tile_size;
        draw_node->drawLine(Vec2(0, y), Vec2(mScrollMapView->getInnerContainerSize().width, y), color);
    }
    
    mScrollMapView->addChild(draw_node, -1);
    mScrollMapView->setSwallowTouches(false);
    
    
    // Button Remove, Insert
    auto mRemoveOnButton = MenuItemImage::create("boxCoinAlt.png","boxCoin_disabled.png");
    auto mRemoveOffButton = MenuItemImage::create("boxCoin_disabled.png","boxCoinAlt.png");
    Vec2 tRemoveButtonPos = Vec2(Vec2(origin.x +visibleSize.width,origin.y + visibleSize.height - 120));
    
    auto tRemoveButton = MenuItemToggle::createWithCallback(CC_CALLBACK_1(MapMakingScene::startRemove, this), mRemoveOffButton, mRemoveOnButton, NULL);
    tRemoveButton->setAnchorPoint(Vec2(1,1));
    tRemoveButton->setPosition(tRemoveButtonPos);
    
    auto mInsertOnButton = MenuItemImage::create("box.png","boxItem.png");
    auto mInsertOffButton = MenuItemImage::create("boxItem.png","box.png");
    Vec2 tInsertButtonPos = Vec2(Vec2(origin.x +visibleSize.width,origin.y + visibleSize.height - 30));
    
    auto tInsertButton = MenuItemToggle::createWithCallback(CC_CALLBACK_1(MapMakingScene::startInsert, this), mInsertOffButton, mInsertOnButton, NULL);
    tInsertButton->setAnchorPoint(Vec2(1,1));
    tInsertButton->setPosition(tInsertButtonPos);
    
    cocos2d::Vector<MenuItem*> items;
    items.pushBack(tRemoveButton);
    items.pushBack(tInsertButton);
    
    auto menu = Menu::createWithArray(items);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(MapMakingScene::onTouchBegan,this);
    listener->onTouchMoved = CC_CALLBACK_2(MapMakingScene::onTouchMoved, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, mScrollMapView);
    
    return true;
}

void MapMakingScene::selectedItemRootListEvent(Ref *sender, ui::ListView::EventType type)
{
    ui::ListView *listView = static_cast<ui::ListView *>(sender);
    
    switch (type) {
        case ui::ListView::EventType::ON_SELECTED_ITEM_START:
            
            break;
        case ui::ListView::EventType::ON_SELECTED_ITEM_END:
            if (mCheckRootItem) {
                CCLOG("go to child item with index root = %ld",listView->getCurSelectedIndex());
                mListButtonChild->removeAllChildren();
                tVectorNameChildItem = mMapNameItem[(int)listView->getCurSelectedIndex()];
                for (int i = 0 ; i < tVectorNameChildItem.size(); i++) {
                    ui::Button *button = ui::Button::create(tVectorNameChildItem[i]);
                    mListButtonChild->pushBackCustomItem(button);
                }
                listView->setVisible(false);
                mListButtonChild->setVisible(true);
                mCheckRootItem = false;
            }
            break;
            
        default:
            break;
    }
    
   
}

void MapMakingScene::selectedItemChildListEvent(Ref *sender, ui::ListView::EventType type)
{
    ui::ListView *listView = static_cast<ui::ListView *>(sender);
    switch (type) {
        case ui::ListView::EventType::ON_SELECTED_ITEM_START:
            
            break;
        case ui::ListView::EventType::ON_SELECTED_ITEM_END:
          
            if (listView->getCurSelectedIndex() != 0) {
                CCLOG("index Child = %ld",listView->getCurSelectedIndex());
                mCurrentNameChild = tVectorNameChildItem[(int)listView->getCurSelectedIndex()];
            }
            else
            {
                mCheckRootItem = true;
                CCLOG("Return Root item");
                listView->setVisible(false);
                mListButonRoot->setVisible(true);
            }
            
            break;
            
        default:
            break;
    }
}
string MapMakingScene::getNameWithNumber(int number)
{
    string rName="";
    switch (number) {
        case 0:
            rName ="castle.png";
            break;
        case 1:
            rName ="boxItem.png";
            break;
        case 2:
            rName ="fence.png";
            break;
        case 3:
            rName ="signRight.png";
            break;
        case 4:
            rName ="tochLit.png";
            break;
        case 5:
            rName ="liquidWaterTop_mid.png";
            break;
        case 6:
            rName ="stoneHalf.png";
            break;
        default:
            break;
    }
    return rName;
}

bool MapMakingScene::onTouchBegan(Touch *touch, Event *event)
{
    if (!mScrollMapView->isTouchEnabled()) {
        
        Vec2 origin = Director::getInstance()->getVisibleOrigin();
        
        switch (mCurrentState) {
            case Insert:
                if ((touch->getLocation().x - mScrollMapView->getInnerContainerPosition().x - visibleSize.width/10)/tile_size >= 0)
                {
                    int numberWidth = (touch->getLocation().x - mScrollMapView->getInnerContainerPosition().x - visibleSize.width/10)/tile_size;
                    int numberHeight = (touch->getLocation().y - mScrollMapView->getInnerContainerPosition().y - origin.y)/tile_size;
                    CCLOG("Insert in Pos of Map numberWidth = %i, numberHeight = %i", numberWidth, numberHeight);
                    
                    
                    string tName =to_string(numberWidth) + "+" + to_string(numberHeight);
                    auto temp = mScrollMapView->getChildByName(tName);
                    if (temp!=NULL) {
                        mScrollMapView->removeChild(temp);
                    }
                    auto tSprite = Sprite::create(mCurrentNameChild);
                    tSprite->setName(tName);
                    tSprite->setAnchorPoint(Vec2(0,0));
                    tSprite->setScale(70/tSprite->getBoundingBox().size.width);
                    tSprite->setPosition(numberWidth*tile_size, numberHeight*tile_size);
                    mScrollMapView->addChild(tSprite);
                }
                break;
            case Remove:
                if ((touch->getLocation().x - mScrollMapView->getInnerContainerPosition().x - visibleSize.width/10)/tile_size >= 0)
                {
                    int numberWidth = (touch->getLocation().x - mScrollMapView->getInnerContainerPosition().x - visibleSize.width/10)/tile_size;
                    int numberHeight = (touch->getLocation().y - mScrollMapView->getInnerContainerPosition().y - origin.y)/tile_size;
                    CCLOG("Remove in Pos of Map numberWidth = %i, numberHeight = %i", numberWidth, numberHeight);
                    string tName =to_string(numberWidth) + "+" + to_string(numberHeight);
                    auto tSprite = mScrollMapView->getChildByName(tName);
                    if (tSprite!=NULL){
                        mScrollMapView->removeChild(tSprite);
                    }
                    
                }
                break;
            case Move:
                break;
            default:
                break;
        }
        

    }

    return true;
}

void MapMakingScene::onTouchMoved(Touch *touch, Event *event)
{
    if (!mScrollMapView->isTouchEnabled()) {
       Vec2 origin = Director::getInstance()->getVisibleOrigin();
        
        switch (mCurrentState) {
            case Insert:
                if ((touch->getLocation().x - mScrollMapView->getInnerContainerPosition().x - visibleSize.width/10)/tile_size >= 0)
                {
                    int numberWidth = (touch->getLocation().x - mScrollMapView->getInnerContainerPosition().x - visibleSize.width/10)/tile_size;
                    int numberHeight = (touch->getLocation().y - mScrollMapView->getInnerContainerPosition().y - origin.y)/tile_size;
                    CCLOG("Insert in Pos of Map numberWidth = %i, numberHeight = %i", numberWidth, numberHeight);
                    string tName =to_string(numberWidth) + "+" + to_string(numberHeight);
                    auto temp = mScrollMapView->getChildByName(tName);
                    if (temp!=NULL) {
                        mScrollMapView->removeChild(temp);
                    }
                    
                    auto tSprite = Sprite::create(mCurrentNameChild);
                    tSprite->setName(tName);
                    tSprite->setAnchorPoint(Vec2(0,0));
                    tSprite->setScale(70/tSprite->getBoundingBox().size.width);
                    tSprite->setPosition(numberWidth*tile_size, numberHeight*tile_size);
                    mScrollMapView->addChild(tSprite);
                }
                break;
            case Remove:
                if ((touch->getLocation().x - mScrollMapView->getInnerContainerPosition().x - visibleSize.width/10)/tile_size >= 0)
                {
                    int numberWidth = (touch->getLocation().x - mScrollMapView->getInnerContainerPosition().x - visibleSize.width/10)/tile_size;
                    int numberHeight = (touch->getLocation().y - mScrollMapView->getInnerContainerPosition().y - origin.y)/tile_size;
                    CCLOG("Remove in Pos of Map numberWidth = %i, numberHeight = %i", numberWidth, numberHeight);
                    string tName =to_string(numberWidth) + "+" + to_string(numberHeight);
                    auto tSprite = mScrollMapView->getChildByName(tName);
                    if (tSprite!=NULL){
                        mScrollMapView->removeChild(tSprite);
                    }
                    
                }
                break;
            case Move:
                break;
            default:
                break;
        }
        
    }
}

void MapMakingScene::startInsert(cocos2d::Ref *pSender)
{
    mCurrentState = Insert;
    mScrollMapView->setTouchEnabled(!mScrollMapView->isTouchEnabled());
    CCLOG("Insert");
}

void MapMakingScene::startRemove(cocos2d::Ref *pSender)
{
    CCLOG("Remove");
    mCurrentState = Remove;
    mScrollMapView->setTouchEnabled(!mScrollMapView->isTouchEnabled());
}


