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
    
    mCheckRootItem = true;
    
    visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    //SETUP SCROLL CONTAINER
    mScaleValue = 1.0f;
    
    
    tile_size = 60;
    auto numberTileWidth = 15;
    auto numberTileHeight = 15;
    for (int i = 0; i < numberTileWidth; i++) {
        for (int j = 0 ; j < numberTileHeight; j++) {
            mMang2Chieu[i][j]=0;
        }
    }
    
    mListButonView = ui::ListView::create();
    mListButonView->setDirection(ui::ScrollView::Direction::VERTICAL);
    mListButonView->setClippingEnabled(false);
    mListButonView->setPosition(Vec2(0,origin.y));
    mListButonView->setContentSize(Size(visibleSize.width/10,visibleSize.height));
    
    
    for (int i = 0; i < 20; i++) {
        ui::Button *button = ui::Button::create("CloseNormal.png","CloseSelected.png");
        mListButonView->pushBackCustomItem(button);
    }
    mListButonView->addEventListener(CC_CALLBACK_2(MapMakingScene::selectedItemListViewEvent, this));
    addChild(mListButonView);
    
    mScrollMapView = ui::ScrollView::create();
    mScrollMapView->setDirection(ui::ScrollView::Direction::BOTH);
    mScrollMapView->setContentSize(Size(visibleSize.width + origin.x, visibleSize.height + origin.y));
    mScrollMapView->setInnerContainerSize(Size(tile_size*numberTileWidth + visibleSize.width/10 + origin.x, tile_size*numberTileHeight + origin.y));
    mScrollMapView->setPosition(Vec2(visibleSize.width/10,origin.y));
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
                                             "CloseNormal.png",
                                             "CloseSelected.png",
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
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, mScrollMapView);
    
    return true;
}

void MapMakingScene::selectedItemListViewEvent(Ref *sender, ui::ListView::EventType type)
{
    ui::ListView *listView = static_cast<ui::ListView *>(sender);
    
    switch (type) {
        case ui::ListView::EventType::ON_SELECTED_ITEM_START:
            
            break;
        case ui::ListView::EventType::ON_SELECTED_ITEM_END:
            if (mCheckRootItem) {
                CCLOG("go to child item with index root = %ld",listView->getCurSelectedIndex());
                mCheckRootItem = false;
            }
            else
            {
                if (listView->getCurSelectedIndex() != 0) {
                    CCLOG("index Child = %ld",listView->getCurSelectedIndex());
                }
                else
                {
                    mCheckRootItem = true;
                    CCLOG("Return Root item");
                }
            }
            break;
            
        default:
            break;
    }
}

bool MapMakingScene::onTouchBegan(Touch *touch, Event *event)
{
    if (!mScrollMapView->isTouchEnabled()) {
        Vec2 origin = Director::getInstance()->getVisibleOrigin();
        int numberWidth = (touch->getLocation().x - mScrollMapView->getInnerContainerPosition().x - visibleSize.width/10)/tile_size;
        int numberHeight = (touch->getLocation().y - mScrollMapView->getInnerContainerPosition().y - origin.y)/tile_size;
        CCLOG("Pos of Map numberWidth = %i, numberHeight = %i", numberWidth, numberHeight);
        auto tSprite = Sprite::create("HelloWorld.png");
        tSprite->setAnchorPoint(Vec2(0,0));
        tSprite->setScale(0.3);
        tSprite->setPosition(numberWidth*tile_size, numberHeight*tile_size);
        mScrollMapView->addChild(tSprite);
    }
    
    return true;
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


