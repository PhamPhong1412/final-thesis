#include "LoginScene.h"


Scene* LoginScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = LoginScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool LoginScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	MenuItemFont* playGame = MenuItemFont::create("ping", CC_CALLBACK_1(LoginScene::menuPlayCallback, this));
	playGame->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 5 + visibleSize.height / 2));

	Menu *mainMenu = Menu::create(playGame, nullptr);
	mainMenu->setPosition(Vec2(0, 0));
	this->addChild(mainMenu);

	return true;
}

void LoginScene::menuPlayCallback(cocos2d::Ref* pSender){
	//cocos2d::network::HttpRequest* request = new cocos2d::network::HttpRequest();
	//request->setUrl("127.0.0.1");
	//request->setRequestType(cocos2d::network::HttpRequest::Type::GET);
	////request->setResponseCallback(CC_CALLBACK_0(cocos2d::network::HttpResponse::getHttpRequest, this));
	//request->setTag("loadGame");
	//cocos2d::network::HttpClient::getInstance()->send(request);cd
	//request->release();
}

