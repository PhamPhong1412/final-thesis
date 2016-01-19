#include "MapMakingScene.h"
#include "GameConfig.h"
#include "LoadingHUDLayer.h"

#define kButtonSize	55
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
    mCurrentNameChild = "1,1.png";
    mMapSave = "";
    mCheckRootItem = true;
    
    mCurrentState = Move;
    tile_size = 70;
    
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
	
    initCreateMapView(false);
    return true;
}

void MapMakingScene::initListItem()
{
    vector<string> tTemp0 = {"signExit.png", "1,1.png","1,2,1.png","2,1.png","2,2,1.png","1,3.png","2,3.png","1,4,1.png","2,4,1.png"};
    vector<string> tTemp1 = {"signExit.png", "1,7"};
    vector<string> tTemp2 = {"signExit.png", "fence.png","door_closedMid.png","door_closedTop.png","fenceBroken.png","door_openTop.png","door_openMid.png","ladder_top.png","ladder_mid.png"};
    vector<string> tTemp3 = {"signExit.png", "1,6.png","1,5.png"};
    vector<string> tTemp4 = {"signExit.png", "tochLit.png","torch.png","tochLit2.png","window.png"};
    vector<string> tTemp5 = {"signExit.png", "liquidWaterTop_mid.png","liquidWaterTop.png","liquidWater.png","liquidLavaTop.png","liquidLavaTop_mid.png","liquidLava.png"};
    vector<string> tTemp6 = {"signExit.png", "stoneHalf.png","stoneHalfLeft.png","stoneHalfMid.png","stoneHalfRight.png","stoneHillLeft2.png","stoneHillRight2.png","stoneMid.png"};
    
    mMapNameItem.push_back(tTemp0);
    mMapNameItem.push_back(tTemp1);
    /* mMapNameItem.push_back(tTemp2);
    mMapNameItem.push_back(tTemp3);
    mMapNameItem.push_back(tTemp4);
    mMapNameItem.push_back(tTemp5);
    mMapNameItem.push_back(tTemp6);*/
}

void MapMakingScene::initScrollMapView(bool isNewMap)
{
	
    mScrollMapView = ui::ScrollView::create();
    mScrollMapView->setDirection(ui::ScrollView::Direction::BOTH);
    mScrollMapView->setContentSize(Size(visibleSize.width - tile_size + origin.x, visibleSize.height + origin.y));
    mScrollMapView->setInnerContainerSize(Size(tile_size*numberTileWidth + origin.x, tile_size*numberTileHeight + origin.y));
    mScrollMapView->setPosition(Vec2(tile_size+origin.x ,origin.y));
    mScrollMapView->setScrollBarEnabled(true);
    mScrollMapView->setBackGroundImage("bg.png");
    mScrollMapView->setBackGroundImageScale9Enabled(true);
	addChild(mScrollMapView);
	if (isNewMap == false)
	{
		std::string map = DBContext::get("map_test");
		cocos2d::log("%s", map.c_str());

		std::vector<std::string> part = Utility::splitString(map, "dm");

		std::vector<std::string> widthHeight = Utility::splitString(part.at(0), "\n");
		/*numberTileWidth = std::stoi(widthHeight.at(0));
		numberTileHeight = std::stoi(widthHeight.at(1));*/
		std::vector<std::string> objectData = Utility::splitString(part.at(1), "\n");
		for (int i = 0; i < numberTileHeight; i++){
			mVector2Chieu.push_back(vector<string>());
			int temp = numberTileHeight - i - 1;
			std::vector<std::string> currentLineData = Utility::splitString(objectData.at(temp), ";");
			for (int j = 0; j < numberTileWidth; j++){
				std::string tileName = currentLineData.at(j);
				mVector2Chieu[i].push_back(tileName);

				if (tileName == "0")
				{
					//continue;
				}
				else
				{
					
					string tName = to_string(j) + "+" + to_string(i);

					string filePath = tileName + ".png";
					auto tSprite = Sprite::create(filePath);
					tSprite->setName(tName);
					tSprite->setAnchorPoint(Vec2(0, 0));
					//tSprite->setScale(GameConfig::scale);
					tSprite->setPosition(j*tile_size, i*tile_size);
					mScrollMapView->addChild(tSprite);
				}
			}
		}

	}
	else
	{

		for (int i = 0; i < numberTileHeight; i++) {
			mVector2Chieu.push_back(vector<string>());
			for (int j = 0; j < numberTileWidth; j++) {

				if (i == 0) {
					mVector2Chieu[i].push_back("1,1");
					string tName = to_string(j) + "+" + to_string(i);
					auto tSprite = Sprite::create("1,1.png");
					tSprite->setName(tName);
					tSprite->setAnchorPoint(Vec2(0, 0));
					//tSprite->setScale(GameConfig::scale);
					tSprite->setPosition(j*tile_size, i*tile_size);
					mScrollMapView->addChild(tSprite);

				}
				else if (i == numberTileHeight - 1)
				{
					mVector2Chieu[i].push_back("1,1");
					string tName = to_string(j) + "+" + to_string(i);
					auto tSprite = Sprite::create("1,1.png");
					tSprite->setName(tName);
					tSprite->setAnchorPoint(Vec2(0, 0));
					//tSprite->setScale(GameConfig::scale);
					tSprite->setPosition(j*tile_size, i*tile_size);
					mScrollMapView->addChild(tSprite);
				}
				else if (i == 1)
				{
					if (j == 0)
					{
						mVector2Chieu[i].push_back("1,6");
						string tName = to_string(j) + "+" + to_string(i);
						auto tSprite = Sprite::create("1,6.png");
						tSprite->setName(tName);
						tSprite->setAnchorPoint(Vec2(0, 0));
						//tSprite->setScale(GameConfig::scale);
						tSprite->setPosition(j*tile_size, i*tile_size);
						mScrollMapView->addChild(tSprite);
					}
					else if (j == numberTileWidth - 1)
					{
						mVector2Chieu[i].push_back("1,5");
						string tName = to_string(j) + "+" + to_string(i);
						auto tSprite = Sprite::create("1,5.png");
						tSprite->setName(tName);
						tSprite->setAnchorPoint(Vec2(0, 0));
						//tSprite->setScale(GameConfig::scale);
						tSprite->setPosition(j*tile_size, i*tile_size);
						mScrollMapView->addChild(tSprite);
					}
					else
					{
						mVector2Chieu[i].push_back("0");
					}
				}
				else
				{
					mVector2Chieu[i].push_back("0");
				}

				if ((j == 0 || j == numberTileWidth - 1) && i > 1 && i < numberTileHeight - 1)
				{
					mVector2Chieu[i].push_back("0");
					string tName = to_string(j) + "+" + to_string(i);
					auto tSprite = Sprite::create("1,1.png");
					tSprite->setName(tName);
					tSprite->setAnchorPoint(Vec2(0, 0));
					//tSprite->setScale(GameConfig::scale);
					tSprite->setPosition(j*tile_size, i*tile_size);
					mScrollMapView->addChild(tSprite);
				}
			}
		}
	}

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
	mScrollMapView->scrollToBottom(0.1,true);
	
}
void MapMakingScene::initAll(bool isNewMap)
{
	
	initListItem();
	// SETUP LIST VIEW CHILD
	initListChild();
	// SETUP LISTVIEW ROOT
	initListRoot();
	// SETUP SCROLL VIEW
	initScrollMapView(isNewMap);
	// Button Remove, Insert, Move
	initButton();
	mCurrentTile = Sprite::create(mCurrentNameChild);
	mCurrentTile->setAnchorPoint(Vec2(0.5, 1));
	mCurrentTile->setScale(70 / mCurrentTile->getBoundingBox().size.width);
	mCurrentTile->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.x + visibleSize.height));

	this->addChild(mCurrentTile);

	auto listener = EventListenerTouchOneByOne::create();

	listener->onTouchBegan = CC_CALLBACK_2(MapMakingScene::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(MapMakingScene::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(MapMakingScene::onTouchEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, mScrollMapView);
}

void MapMakingScene::initCreateMapView(bool withBackground)
{
	auto chooseLayer = new WidthHeightChooseHUD(this, withBackground, withBackground);
    chooseLayer->setDelegate(this);
    //this->removeChild(menu);
    this->addChild(chooseLayer);
    isChooseInfo = true;
}

void MapMakingScene::exitBack(int width, int height)
{
    numberTileWidth = width;
    numberTileHeight = height;
    CCLOG("%d%d",width, height);
    // INIT LOCAL DATA
	
	initAll(true);

}

void MapMakingScene::loadLocalMap()
{
	std::string map = DBContext::get("map_test");
	std::vector<std::string> part = Utility::splitString(map, "dm");

	std::vector<std::string> widthHeight = Utility::splitString(part.at(0), "\n");
	numberTileWidth = std::stoi(widthHeight.at(0));
	numberTileHeight = std::stoi(widthHeight.at(1));
	initAll(false);
}

void MapMakingScene::initListChild()
{
    mListButtonChild = ui::ListView::create();
    mListButtonChild->setDirection(ui::ScrollView::Direction::VERTICAL);
    mListButtonChild->setClippingEnabled(false);
    mListButtonChild->setBounceEnabled(true);
    mListButtonChild->setPosition(Vec2(origin.x,origin.y));
    mListButtonChild->setContentSize(Size(tile_size + origin.x,visibleSize.height));
    mListButtonChild->setItemsMargin(10);
    mListButtonChild->addEventListener((ui::ListView::ccListViewCallback)CC_CALLBACK_2(MapMakingScene::selectedItemChildListEvent, this));
    mListButtonChild->setBackGroundColorType(cocos2d::ui::LayoutBackGroundColorType::SOLID);
    mListButtonChild->setScrollBarEnabled(false);
    mListButtonChild->setBackGroundColor(Color3B( 0, 255, 0));
    mListButtonChild->setVisible(false);
    addChild(mListButtonChild);
}

void MapMakingScene::initListRoot()
{
    mListButonRoot = ui::ListView::create();
    mListButonRoot->setDirection(ui::ScrollView::Direction::VERTICAL);
    mListButonRoot->setClippingEnabled(false);
    mListButonRoot->setBounceEnabled(true);
    mListButonRoot->setPosition(Vec2(origin.x,origin.y));
    mListButonRoot->setContentSize(Size(tile_size+ origin.x ,visibleSize.height));
    for (int i =0 ; i<mMapNameItem.size() ; i++) {
        ui::Button *button = ui::Button::create(getNameWithNumber(i));
        //button->setScale(GameConfig::scale);
        mListButonRoot->pushBackCustomItem(button);
    }
    
    mListButonRoot->setItemsMargin(10);
    mListButonRoot->addEventListener((ui::ListView::ccListViewCallback)CC_CALLBACK_2(MapMakingScene::selectedItemRootListEvent, this));
    mListButonRoot->setBackGroundColorType(cocos2d::ui::LayoutBackGroundColorType::SOLID);
    mListButonRoot->setScrollBarEnabled(false);
    mListButonRoot->setBackGroundColor(Color3B( 0, 255, 0));
    addChild(mListButonRoot);

}

void MapMakingScene::initButton()
{
    Vec2 tMoveButtonPos = Vec2(Vec2(origin.x +visibleSize.width,origin.y + visibleSize.height ));
    
    mMoveButton = MenuItemImage::create("MoveSelected.png","MoveNormal.png",CC_CALLBACK_1(MapMakingScene::startMove,this));
    
    mMoveButton->setAnchorPoint(Vec2(1,1));
    mMoveButton->setScale(kButtonSize/mMoveButton->getNormalImage()->getContentSize().width);
    mMoveButton->setPosition(tMoveButtonPos);
    
	Vec2 tRemoveButtonPos = Vec2(Vec2(origin.x + visibleSize.width, origin.y + visibleSize.height - kButtonSize - 10));
    
    mRemoveButton = MenuItemImage::create("RemoveSelected.png","RemoveNormal.png",CC_CALLBACK_1(MapMakingScene::startRemove,this));
    mRemoveButton->setAnchorPoint(Vec2(1,1));
	mRemoveButton->setScale(kButtonSize / mRemoveButton->getNormalImage()->getContentSize().width);
    mRemoveButton->setPosition(tRemoveButtonPos);
    
	Vec2 tInsertButtonPos = Vec2(Vec2(origin.x + visibleSize.width, origin.y + visibleSize.height - kButtonSize * 2 - 20));
    
    mInsertButton = MenuItemImage::create("AddSelected.png","AddNormal.png",CC_CALLBACK_1(MapMakingScene::startInsert,this));
	mInsertButton->setScale(kButtonSize / mInsertButton->getNormalImage()->getContentSize().width);
    mInsertButton->setAnchorPoint(Vec2(1,1));
    mInsertButton->setPosition(tInsertButtonPos);
    
    auto tSaveButton = MenuItemImage::create("SaveSelected.png","SaveNormal.png",  CC_CALLBACK_1(MapMakingScene::saveMap, this));
    tSaveButton->setAnchorPoint(Vec2(1,1));
	tSaveButton->setScale(kButtonSize / tSaveButton->getNormalImage()->getContentSize().width);
	tSaveButton->setPosition(origin.x + visibleSize.width, origin.y + visibleSize.height - kButtonSize * 4 - 40);
 
	auto tFlipButton = MenuItemImage::create("ChangeSelected.png", "ChangeNormal.png", CC_CALLBACK_1(MapMakingScene::flipTile, this));
	tFlipButton->setAnchorPoint(Vec2(1, 1));
	tFlipButton->setScale(kButtonSize / tFlipButton->getNormalImage()->getContentSize().width);
	tFlipButton->setPosition(origin.x + visibleSize.width, origin.y + visibleSize.height - kButtonSize * 3 - 30);

	auto tHelpButton = MenuItemImage::create("Help2.png", "Help1.png", CC_CALLBACK_1(MapMakingScene::helpPress, this));
	tHelpButton->setAnchorPoint(Vec2(1, 1));
	tHelpButton->setScale(kButtonSize / tHelpButton->getNormalImage()->getContentSize().width);
	tHelpButton->setPosition(origin.x + visibleSize.width, origin.y + visibleSize.height - kButtonSize * 5 - 50);

    mMoveButton->selected();
    mRemoveButton->unselected();
    mInsertButton->unselected();
    
    cocos2d::Vector<MenuItem*> items;
    items.pushBack(mInsertButton);
    items.pushBack(mRemoveButton);
    items.pushBack(mMoveButton);
    items.pushBack(tSaveButton);
    items.pushBack(tFlipButton);
	items.pushBack(tHelpButton);

    menu = Menu::createWithArray(items);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

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
                    //button->setScale(GameConfig::scale);
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
				mCurrentTile->setTexture(mCurrentNameChild);
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
            rName ="1,1.png";
            break;
        case 1:
            rName ="1,7.png";
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
                if ((touch->getLocation().x - mScrollMapView->getInnerContainerPosition().x - origin.x - (tile_size))/tile_size >= 0)
                {
                    int numberWidth = (touch->getLocation().x - mScrollMapView->getInnerContainerPosition().x - origin.x -(tile_size))/tile_size;
                    int numberHeight = (touch->getLocation().y - mScrollMapView->getInnerContainerPosition().y - origin.y)/tile_size;
                    CCLOG("Insert in Pos of Map numberWidth = %i, numberHeight = %i", numberWidth, numberHeight);
					if (numberWidth == 0 || numberWidth == 1 || numberWidth == numberTileWidth - 2 || numberWidth == numberTileWidth - 1 || numberHeight == 0 || numberHeight == numberTileHeight - 1 || numberHeight == numberTileHeight - 2)
					{
						return true;
					}
                    

                    string tName =to_string(numberWidth) + "+" + to_string(numberHeight);
                    auto temp = mScrollMapView->getChildByName(tName);
                    if (temp!=NULL) {
                        mScrollMapView->removeChild(temp);
                    }
                    
                    auto tSprite = Sprite::create(mCurrentNameChild);
                    string tPng = ".png";
                    
                    string tNameFile = mCurrentNameChild;
                    string::size_type i = tNameFile.find(tPng);
                    if (i != std::string::npos)
                        tNameFile.erase(i, tPng.length());
                    
                    mVector2Chieu[numberHeight][numberWidth] =  tNameFile;
                    
                    tSprite->setName(tName);
                    tSprite->setAnchorPoint(Vec2(0,0));
                    tSprite->setScale(70/tSprite->getBoundingBox().size.width);
                    tSprite->setPosition(numberWidth*tile_size, numberHeight*tile_size);
                    mScrollMapView->addChild(tSprite);
                }
                break;
            case Remove:
                if ((touch->getLocation().x - mScrollMapView->getInnerContainerPosition().x - origin.x - (tile_size))/tile_size >= 0)
                {
                    int numberWidth = (touch->getLocation().x - mScrollMapView->getInnerContainerPosition().x - origin.x - (tile_size))/tile_size;
                    int numberHeight = (touch->getLocation().y - mScrollMapView->getInnerContainerPosition().y - origin.y)/tile_size;
                    CCLOG("Remove in Pos of Map numberWidth = %i, numberHeight = %i", numberWidth, numberHeight);
					if (numberWidth == 0 || numberWidth == 1 || numberWidth == numberTileWidth - 2 || numberWidth == numberTileWidth - 1 || numberHeight == 0 || numberHeight == numberTileHeight - 1 || numberHeight == numberTileHeight - 2)
					{
						return true;
					}
                    string tName =to_string(numberWidth) + "+" + to_string(numberHeight);
                    auto tSprite = mScrollMapView->getChildByName(tName);
                    if (tSprite!=NULL){
                        mScrollMapView->removeChild(tSprite);
                        mVector2Chieu[numberHeight][numberWidth] = "0";
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
                if ((touch->getLocation().x - mScrollMapView->getInnerContainerPosition().x - origin.x - (tile_size))/tile_size >= 0)
                {
                    int numberWidth = (touch->getLocation().x - mScrollMapView->getInnerContainerPosition().x - origin.x - (tile_size))/tile_size;
                    int numberHeight = (touch->getLocation().y - mScrollMapView->getInnerContainerPosition().y - origin.y)/tile_size;
                    CCLOG("Insert in Pos of Map numberWidth = %i, numberHeight = %i", numberWidth, numberHeight);
					if (numberWidth == 0 || numberWidth == 1 || numberWidth == numberTileWidth - 2 || numberWidth == numberTileWidth - 1 || numberHeight == 0 || numberHeight == numberTileHeight - 1 || numberHeight == numberTileHeight - 2)
					{
						return;
					}
                    string tName =to_string(numberWidth) + "+" + to_string(numberHeight);
                    auto temp = mScrollMapView->getChildByName(tName);
                    if (temp!=NULL) {
                        mScrollMapView->removeChild(temp);
                    }
                    
                    auto tSprite = Sprite::create(mCurrentNameChild);
                    
                    string tPng = ".png";
                    string tNameFile = mCurrentNameChild;
                    string::size_type i = tNameFile.find(tPng);
                    if (i != std::string::npos)
                        tNameFile.erase(i, tPng.length());
                    
                    mVector2Chieu[numberHeight][numberWidth] = tNameFile;
                    tSprite->setName(tName);
                    tSprite->setAnchorPoint(Vec2(0,0));
                    tSprite->setScale(70/tSprite->getBoundingBox().size.width);
                    tSprite->setPosition(numberWidth*tile_size, numberHeight*tile_size);
                    mScrollMapView->addChild(tSprite);
                }
                break;
            case Remove:
                if ((touch->getLocation().x - mScrollMapView->getInnerContainerPosition().x - origin.x - (tile_size))/tile_size >= 0)
                {
                    int numberWidth = (touch->getLocation().x - mScrollMapView->getInnerContainerPosition().x - origin.x - (tile_size))/tile_size;
                    int numberHeight = (touch->getLocation().y - mScrollMapView->getInnerContainerPosition().y - origin.y)/tile_size;
                    CCLOG("Remove in Pos of Map numberWidth = %i, numberHeight = %i", numberWidth, numberHeight);
					if (numberWidth == 0 || numberWidth == 1 || numberWidth == numberTileWidth - 2 || numberWidth == numberTileWidth - 1 || numberHeight == 0 || numberHeight == numberTileHeight - 1 || numberHeight == numberTileHeight - 2)
					{
						return;
					}
                    string tName =to_string(numberWidth) + "+" + to_string(numberHeight);
                    auto tSprite = mScrollMapView->getChildByName(tName);
                    if (tSprite!=NULL){
                        mScrollMapView->removeChild(tSprite);
                        mVector2Chieu[numberHeight][numberWidth] = "0";
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

void MapMakingScene::onTouchEnded(Touch *touch, Event *event)
{
    
}

void MapMakingScene::helpPress(cocos2d::Ref* pSender)
{
	CCLOG("HELP");
}

void MapMakingScene::flipTile(cocos2d::Ref *pSender)
{
	string tPng = ".png";

	string tNameFile = mCurrentNameChild;
	string::size_type i = tNameFile.find(tPng);
	if (i != std::string::npos)
		tNameFile.erase(i, tPng.length());

	std::vector<std::string> tTypeObject = Utility::splitString(tNameFile, ",");
	if (tTypeObject.size() == 2)
		return;
	std::string tType = tTypeObject[1];
	std::string tFlip = tTypeObject[2];
	if (tType == "2" || tType == "4")
	{
		tFlip = tFlip == "1" ? "2" : "1";
		mCurrentNameChild = tTypeObject[0] + "," + tType + "," + tFlip + ".png";
		mCurrentTile->setTexture(mCurrentNameChild);
	}
}

void MapMakingScene::saveMap(cocos2d::Ref *pSender)
{
    mMapSave = "";
    mMapSave = to_string(numberTileWidth)+"\n"+to_string(numberTileHeight)+"\n" +"dm";

    for (int i = numberTileHeight-1 ; i>=0; i--) {
        for (int j = 0 ; j < numberTileWidth ; j++) {
		

            if (j == numberTileWidth-1) 
			{
				if (i > 1 && i < numberTileHeight - 1)
				{
					mMapSave += "1,1\n";
				}
				else
				{
					mMapSave += mVector2Chieu[i][j] + "\n";
				}
               
            }
			else if (j == 0)
			{
				if (i > 1 && i < numberTileHeight - 1)
				{
					mMapSave += "1,1;";
				}
				else
				{
					mMapSave += mVector2Chieu[i][j] + ";";
				}
			}
            else
            {
               mMapSave += mVector2Chieu[i][j]+";";
            }
        }
    }
    
    cocos2d::log("%s", mMapSave.c_str());
	DBContext::set("map_test", mMapSave.c_str());
    std::string test = DBContext::get("map_test");
	auto gameScene = MainGameScene::createScene(true, test, HttpShortMapInfo());
	Director::getInstance()->replaceScene(gameScene);
}

void MapMakingScene::startMove(cocos2d::Ref *pSender)
{
    mCurrentState = Move;
    mScrollMapView->setTouchEnabled(true);
    mMoveButton->selected();
    mRemoveButton->unselected();
    mInsertButton->unselected();
    CCLOG("Move");
}

void MapMakingScene::startInsert(cocos2d::Ref *pSender)
{
    mCurrentState = Insert;
    mScrollMapView->setTouchEnabled(false);
    mInsertButton->selected();
    mMoveButton->unselected();
    mRemoveButton->unselected();
    CCLOG("Insert");
}

void MapMakingScene::startRemove(cocos2d::Ref *pSender)
{
    CCLOG("Remove");
    mCurrentState = Remove;
    mMoveButton->unselected();
    mRemoveButton->selected();
    mInsertButton->unselected();
    mScrollMapView->setTouchEnabled(false);
}