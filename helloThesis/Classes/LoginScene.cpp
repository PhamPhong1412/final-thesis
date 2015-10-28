//#include "LoginScene.h"
//
//
//Scene* LoginScene::createScene()
//{
//	// 'scene' is an autorelease object
//	auto scene = Scene::create();
//
//	// 'layer' is an autorelease object
//	auto layer = LoginScene::create();
//
//	// add layer as a child to scene
//	scene->addChild(layer);
//
//	// return the scene
//	return scene;
//}
//
//// on "init" you need to initialize your instance
//bool LoginScene::init()
//{
//	//////////////////////////////
//	// 1. super init first
//	if (!Layer::init())
//	{
//		return false;
//	}
//
//	Size visibleSize = Director::getInstance()->getVisibleSize();
//	Vec2 origin = Director::getInstance()->getVisibleOrigin();
//
//
//	MenuItemFont* playGame = MenuItemFont::create("ping", CC_CALLBACK_1(LoginScene::menuPlayCallback, this));
//	playGame->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 5 + visibleSize.height / 2));
//
//	Menu *mainMenu = Menu::create(playGame, nullptr);
//	mainMenu->setPosition(Vec2(0, 0));
//	this->addChild(mainMenu);
//
//	return true;
//}
//
//void LoginScene::menuPlayCallback(cocos2d::Ref* pSender){
//	HttpRequest* request = new (std::nothrow) HttpRequest();
//	request->setUrl("127.0.0.1");
//	request->setRequestType(HttpRequest::Type::GET);
//	request->setResponseCallback(CC_CALLBACK_2(LoginScene::onHttpRequestCompleted, this));
//	if (false)
//	{
//		request->setTag("GET immediate test1");
//		HttpClient::getInstance()->sendImmediate(request);
//	}
//	else
//	{
//		request->setTag("GET test1");
//		HttpClient::getInstance()->send(request);
//	}
//	request->release();
//}
//
//void LoginScene::onHttpRequestCompleted(HttpClient *sender, HttpResponse *response)
//{
//	if (!response)
//	{
//		return;
//	}
//
//	// You can get original request type from: response->request->reqType
//	if (0 != strlen(response->getHttpRequest()->getTag()))
//	{
//		log("%s completed", response->getHttpRequest()->getTag());
//	}
//
//	long statusCode = response->getResponseCode();
//	char statusString[64] = {};
//	sprintf(statusString, "HTTP Status Code: %ld, tag = %s", statusCode, response->getHttpRequest()->getTag());
//	log("status string %s ", statusString);
//	log("response code: %ld", statusCode);
//
//	if (!response->isSucceed())
//	{
//		log("response failed");
//		log("error buffer: %s", response->getErrorBuffer());
//		return;
//	}
//
//	// dump data
//	std::vector<char> *buffer = response->getResponseData();
//	log("Http Test, dump data: ");
//	for (unsigned int i = 0; i < buffer->size(); i++)
//	{
//		log("%c", (*buffer)[i]);
//	}
//	log("\n");
//	if (response->getHttpRequest()->getReferenceCount() != 2)
//	{
//		log("request ref count not 2, is %d", response->getHttpRequest()->getReferenceCount());
//	}
//}
