#include "MainMenuScene.h"


Scene* MainMenuScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = MainMenuScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool MainMenuScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	std::string s = "abdf \t fwef";
	Utility::splitString(s, "\t");

    initButton();
	return true;
}

void MainMenuScene::initButton()
{
    auto mBackGround = Sprite::create("bg3.png");
    mBackGround->setScale(visibleSize.height/mBackGround->getContentSize().height);
    mBackGround->setAnchorPoint(Vec2(0.5,0.5));
    mBackGround->setPosition((origin.x +visibleSize.width)/2, (origin.y +visibleSize.height)/2);
    addChild(mBackGround);
    
    auto mNameSprite = Sprite::create("GameName.png");
    mNameSprite->setScale((visibleSize.width/2)/mNameSprite->getContentSize().width);
    mNameSprite->setAnchorPoint(Vec2(0.5,1));
    mNameSprite->setPosition(Vec2((origin.x +visibleSize.width)/2,origin.y + visibleSize.height - 50));
    addChild(mNameSprite);
    
    auto mRaceButton = MenuItemImage::create("RaceNormal.png","RaceSelected.png",CC_CALLBACK_1(MainMenuScene::menuPlayCallback,this));

    mRaceButton->setAnchorPoint(Vec2(0.5,0.5));
    mRaceButton->setScale((visibleSize.width/5)/mRaceButton->getNormalImage()->getContentSize().width);
    Vec2 tRaceButtonPos = Vec2((origin.x +visibleSize.width)/2,(origin.y + visibleSize.height)/2 + mRaceButton->getNormalImage()->getContentSize().height/3);
    mRaceButton->setPosition(tRaceButtonPos);
    
    
    
    auto mMapButton = MenuItemImage::create("MapNormal.png","MapSelected.png",CC_CALLBACK_1(MainMenuScene::menuMakeMapCallback,this));
    mMapButton->setAnchorPoint(Vec2(0.5,0.5));
    mMapButton->setScale((visibleSize.width/5)/mMapButton->getNormalImage()->getContentSize().width);
    Vec2 tMapButtonPos = Vec2((origin.x +visibleSize.width)/2,(origin.y + visibleSize.height)/2 - mMapButton->getNormalImage()->getContentSize().height/3);
    mMapButton->setPosition(tMapButtonPos);
    
    
    auto mSettingButton = MenuItemImage::create("SettingNormal.png","SettingSelected.png",CC_CALLBACK_1(MainMenuScene::menuSettingCallback,this));
    mSettingButton->setScale((visibleSize.width/12)/mSettingButton->getNormalImage()->getContentSize().width);
    mSettingButton->setAnchorPoint(Vec2(0.5,1));
	Vec2 tSettingButtonPos = Vec2((origin.x + visibleSize.width) / 4, mMapButton->getPosition().y + 50);
    mSettingButton->setPosition(tSettingButtonPos);
    
    auto tShopButton = MenuItemImage::create("ShopNormal.png","ShopSelected.png",  CC_CALLBACK_1(MainMenuScene::menuShopCallback, this));
    tShopButton->setAnchorPoint(Vec2(0.5,1));
    tShopButton->setScale(visibleSize.width/12/tShopButton->getNormalImage()->getContentSize().width);
	tShopButton->setPosition((origin.x + visibleSize.width) / 4 * 3, mMapButton->getPosition().y + 50);
    
    cocos2d::Vector<MenuItem*> items;
    items.pushBack(mRaceButton);
    items.pushBack(mMapButton);
    items.pushBack(mSettingButton);
    items.pushBack(tShopButton);
    
    auto menu = Menu::createWithArray(items);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    
    
}

void MainMenuScene::menuPlayCallback(cocos2d::Ref *pSender)
{
	auto rankScene = RankingScene::createScene();
	Director::getInstance()->replaceScene(rankScene);
}

void MainMenuScene::transitionToGameScene()
{
	auto size = Director::getInstance()->getWinSize();      //get the windows size.

	auto clipper = ClippingNode::create();      // create the ClippingNode object

	auto stencil = DrawNode::create();      // create the DrawNode object which can draw dots, segments and polygons.

	Point triangle[3];      // init the  triangle vertexes. here my win size is 360x640, so my triangle vertexes init by these values. You can change the values to adapt your scree.
	triangle[0] = Point(-size.width * 1.5f, -size.height / 2);
	triangle[1] = Point(size.width * 1.5f, -size.height / 2);
	triangle[2] = Point(0, size.height);
	Color4F green(0, 1, 0, 1);

	stencil->drawPolygon(triangle, 3, green, 0, green);     //use the drawNode to draw the triangle to cut the ClippingNode.

	clipper->setAnchorPoint(Point(0.5f, 0.5f));     // set the ClippingNode anchorPoint, to make sure the drawNode at the center of ClippingNode
	clipper->setPosition(size.width / 2, size.height / 2);
	clipper->setStencil(stencil);   //set the cut triangle in the ClippingNode.
	clipper->setInverted(true);     //make sure the content is show right side.

	Sprite* blackRect = Sprite::create("HelloWorld.png");     //create a black screen sprite to make sure the bottom is black. the"black_screen.png" is a "black screen" png. 

	clipper->addChild(blackRect);   //to make sure the cover is black.

	this->addChild(clipper, 500);

	// the Clipping node triangle  add some actions to make the triangle scale and rotate.  
	stencil->runAction(EaseSineOut::create(Spawn::create(ScaleTo::create(2.5f, 0.0f, 0.0f), RotateBy::create(2.5f, 540),
		Sequence::create(DelayTime::create(2.5), CallFunc::create(this, callfunc_selector(MainMenuScene::toGameScene)), NULL), NULL)));

}

void MainMenuScene::toGameScene()
{
	//get the game scene and run it.
	auto gameScene = MainGameScene::createScene();
	Director::getInstance()->replaceScene(gameScene);
}

void MainMenuScene::menuMakeMapCallback(cocos2d::Ref *pSender)
{
    auto mapMakingScene = MapMakingScene::createScene();
    Director::getInstance()->replaceScene(mapMakingScene);
}

void MainMenuScene::menuShopCallback(cocos2d::Ref *pSender)
{
    auto shopScene = ShopScene::createScene();
    Director::getInstance()->replaceScene(shopScene);
}

void MainMenuScene::menuSettingCallback(cocos2d::Ref *pSender)
{
    CCLOG("Setting");
}

void MainMenuScene::menuExitCallback(cocos2d::Ref* pSender){
	Director::getInstance()->end();
}
