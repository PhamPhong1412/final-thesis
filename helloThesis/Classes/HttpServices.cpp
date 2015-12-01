#include "HttpServices.h"
#include <string>
#include "spine/Json.h"

USING_NS_CC;
//USING_NS_CC_EXT;
using namespace cocos2d::network;
HttpServices* HttpServices::inst = new HttpServices();

Scene* HttpServices::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease obsject
	auto layer = HttpServices::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool HttpServices::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	const int MARGIN = 40;
	const int SPACE = 35;

	const int LEFT = visibleSize.width / 2;

	auto menuRequest = Menu::create();
	menuRequest->setPosition(Vec2::ZERO);
	addChild(menuRequest);

	// Post
	auto labelPost = Label::createWithTTF("Test Post", "fonts/arial.ttf", 22);
	auto itemPost = MenuItemLabel::create(labelPost, CC_CALLBACK_1(HttpServices::onMenuPostTestClicked, this, false, ""));
	itemPost->setPosition(LEFT, visibleSize.height - MARGIN - 2 * SPACE);
	menuRequest->addChild(itemPost);

	// Response Code Label
	_labelStatusCode = Label::createWithTTF("HTTP Status Code", "fonts/arial.ttf", 18);
	_labelStatusCode->setPosition(visibleSize.width / 2, visibleSize.height - MARGIN - 6 * SPACE);
	addChild(_labelStatusCode);

	return true;
}


void HttpServices::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}


void HttpServices::onHttpRequestCompleted(HttpClient *sender, HttpResponse *response, std::string uid)
{
	if (!response)
	{
		return;
	}
	
	// You can get original request type from: response->request->reqType
	//if (0 != strlen(response->getHttpRequest()->getTag()))
	//{
	//	log("%s completed", response->getHttpRequest()->getTag());
	//}

	//long statusCode = response->getResponseCode();
	//char statusString[64] = {};
	//sprintf(statusString, "HTTP Status Code: %ld, tag = %s", statusCode, response->getHttpRequest()->getTag());
	//_labelStatusCode->setString(statusString);
	//log("response code: %ld", statusCode);

	//if (!response->isSucceed())
	//{
	//	log("response failed");
	//	log("error buffer: %s", response->getErrorBuffer());
	//	return;
	//}

	/*std::vector<char> *buffer = response->getResponseData();	

	char * concatenated = (char *)malloc(buffer->size() + 1);
	std::string s2(buffer->begin(), buffer->end());
	strcpy(concatenated, s2.c_str());

	Json * json = Json_create(concatenated);
	const char * test1 = Json_getString(json, "result", "default");
	const char * test2 = Json_getString(json, "time_server", "default");*/

	mDelegate->getUID("phong khung");
	hideLoading();
}

void HttpServices::onMenuPostTestClicked(cocos2d::Ref *sender, bool isImmediate, std::string uid)
{
	showLoading((Layer*)sender);
	HttpRequest* request = new (std::nothrow) HttpRequest();
	request->setUrl("localhost:8090/runner");
	request->setRequestType(HttpRequest::Type::POST);
	request->setResponseCallback(CC_CALLBACK_2(HttpServices::onHttpRequestCompleted, this, uid));

	// write the post data
	const char* postData = "{\"method\":\"uploadMap\", \"data\":{}}";
	request->setRequestData(postData, strlen(postData));
	if (isImmediate)
	{
		HttpClient::getInstance()->sendImmediate(request);
	}
	else
	{
		HttpClient::getInstance()->send(request);
	}
	request->release();
}


void HttpServices::onMenuPostBinaryTestClicked(cocos2d::Ref *sender, bool isImmediate)
{
	
}

void HttpServices::showLoading(Layer *layer)
{
	auto sprite = Sprite::create("1,1.png");
	sprite->setPosition(Vec2(300, 300));
	sprite->setTag(1111);
	mCurrentLayer = layer;
	layer->addChild(sprite);
}

void HttpServices::hideLoading()
{
	mCurrentLayer->removeChildByTag(1111);
}
