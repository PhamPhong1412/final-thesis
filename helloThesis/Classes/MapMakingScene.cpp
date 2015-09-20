#include "MapMakingScene.h"

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
    mCurrentNameRoot = "";
    mCurrentNameChild = "";
    mCheckRootItem = true;
    
    visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    //SETUP SCROLL CONTAINER
    mScaleValue = 1.0f;
    
    tile_size = 70;
    auto numberTileWidth = 40;
    auto numberTileHeight = 60;
    for (int i = 0; i < numberTileWidth; i++) {
        for (int j = 0 ; j < numberTileHeight; j++) {
            //mMang2Chieu[i][j]="1";
        }
    }
    
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
    
    
    
    mListButonRoot = ui::ListView::create();
    mListButonRoot->setDirection(ui::ScrollView::Direction::VERTICAL);
    mListButonRoot->setClippingEnabled(false);
    mListButonRoot->setPosition(Vec2(0,origin.y));
    mListButonRoot->setContentSize(Size(visibleSize.width/10,visibleSize.height));
    for (int i =0 ; i<mMapItem.size() ; i++) {
        ui::Button *button = ui::Button::create(getNameWithNumber(i));
        mListButonRoot->pushBackCustomItem(button);
    }
    
    mListButonRoot->setItemsMargin(10);
	mListButonRoot->addEventListener((ui::ListView::ccListViewCallback)CC_CALLBACK_2(MapMakingScene::selectedItemRootListEvent, this));
    mListButonRoot->setScrollBarEnabled(false);
    mListButonRoot->setBackGroundImageScale9Enabled(true);
    mListButonRoot->setBackGroundImage("bg_castle.png");
    addChild(mListButonRoot);
    
    
    mScrollMapView = ui::ScrollView::create();
    mScrollMapView->setDirection(ui::ScrollView::Direction::BOTH);
    mScrollMapView->setContentSize(Size(visibleSize.width + origin.x, visibleSize.height + origin.y));
    mScrollMapView->setInnerContainerSize(Size(tile_size*numberTileWidth + visibleSize.width/10 + origin.x, tile_size*numberTileHeight + origin.y));
    mScrollMapView->setPosition(Vec2(visibleSize.width/10,origin.y));
    mScrollMapView->setScrollBarEnabled(false);
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
   
    
    auto settingItem = MenuItemImage::create(
                                             "box.png",
                                             "boxItem.png",
                                             CC_CALLBACK_1(MapMakingScene::zoomIn, this));
    
    Vec2 settingButtonPos = Vec2(Vec2(origin.x +visibleSize.width,origin.y + visibleSize.height - 30));
    settingItem->setAnchorPoint(Vec2(1,1));
    settingItem->setPosition(settingButtonPos);

    cocos2d::Vector<MenuItem*> items;
    items.pushBack(settingItem);
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
               tVectorNameChildItem = mMapItem.find(MapMakingScene::getNameWithNumber((int)listView->getCurSelectedIndex()))->second;
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
        if ((touch->getLocation().x - mScrollMapView->getInnerContainerPosition().x - visibleSize.width/10)/tile_size >= 0)
        {
            int numberWidth = (touch->getLocation().x - mScrollMapView->getInnerContainerPosition().x - visibleSize.width/10)/tile_size;
            int numberHeight = (touch->getLocation().y - mScrollMapView->getInnerContainerPosition().y - origin.y)/tile_size;
            CCLOG("Pos of Map numberWidth = %i, numberHeight = %i", numberWidth, numberHeight);
            auto tSprite = Sprite::create(mCurrentNameChild);
            tSprite->setAnchorPoint(Vec2(0,0));
            tSprite->setScale(70/tSprite->getBoundingBox().size.width);
            tSprite->setPosition(numberWidth*tile_size, numberHeight*tile_size);
            mScrollMapView->addChild(tSprite);
        }
    }

    return true;
}

void MapMakingScene::onTouchMoved(Touch *touch, Event *event)
{
    if (!mScrollMapView->isTouchEnabled()) {
        Vec2 origin = Director::getInstance()->getVisibleOrigin();
        if ((touch->getLocation().x - mScrollMapView->getInnerContainerPosition().x - visibleSize.width/10)/tile_size >= 0)
        {
            int numberWidth = (touch->getLocation().x - mScrollMapView->getInnerContainerPosition().x - visibleSize.width/10)/tile_size;
            int numberHeight = (touch->getLocation().y - mScrollMapView->getInnerContainerPosition().y - origin.y)/tile_size;
            CCLOG("Pos of Map numberWidth = %i, numberHeight = %i", numberWidth, numberHeight);
            auto tSprite = Sprite::create(mCurrentNameChild);
            tSprite->setAnchorPoint(Vec2(0,0));
            tSprite->setScale(70/tSprite->getBoundingBox().size.width);
            tSprite->setPosition(numberWidth*tile_size, numberHeight*tile_size);
            mScrollMapView->addChild(tSprite);
        }
    }
}

void MapMakingScene::zoomIn(cocos2d::Ref *pSender)
{
    mScrollMapView->setTouchEnabled(!mScrollMapView->isTouchEnabled());
}

void MapMakingScene::zoomOut(cocos2d::Ref *pSender)
{
    //mScaleValue += 0.1f;
    //map->setScale(mScaleValue);
}


