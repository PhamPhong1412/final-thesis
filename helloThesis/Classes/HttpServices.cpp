#include "HttpServices.h"

HttpServices* HttpServices::inst = new HttpServices();


void HttpServices::onHttpRequestCompleted(HttpClient *sender, HttpResponse *response, HttpRequestMethod method)
{

	std::vector<char> *buffer = response->getResponseData();	
	if (buffer->size() != 0){
		hideLoading(false);
		return;
	}

	char * concatenated = (char *)malloc(buffer->size() + 1);
	std::string s2(buffer->begin(), buffer->end());
	Utility::strcpy(concatenated, s2.c_str());

	Json * json = Json_create(concatenated);
	//CC_SAFE_DELETE(concatenated);
	const char * result = Json_getString(json, "result", "fail");

	if (result == "fail"){
		hideLoading(false);
		return;
	}

	const char * test2 = Json_getString(json, "time_server", "default");

	returnDelegate(method, Json_getItem(json, "data"));
	//mDelegate->getUID("phong khung");

	hideLoading(true);
}

void HttpServices::sendRequest(cocos2d::Ref *sender, std::vector<HttpRequestParameter> RequestParameter, HttpRequestMethod method, bool isImmediate)
{
	showLoading((Layer*)sender);

	HttpRequest* request = new (std::nothrow) HttpRequest();
	request->setUrl("localhost:8090/runner");
	request->setRequestType(HttpRequest::Type::POST);
	request->setResponseCallback(CC_CALLBACK_2(HttpServices::onHttpRequestCompleted, this, method));

	// write the post data
	std::string methodName = getMethodName(method);
	std::string phoneID = Utility::getPhoneID();

	RequestParameter.push_back(HttpRequestParameter("method", methodName));
	RequestParameter.push_back(HttpRequestParameter("phoneID", phoneID));
	char* jsonData = Utility::buildJson(RequestParameter);
	request->setRequestData(jsonData, strlen(jsonData));

	//const char* postData = "{\"method\":\"uploadMap\", \"data\":{}}";
	//request->setRequestData(postData, strlen(postData));
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

void HttpServices::showLoading(Layer* layer)
{
	auto sprite = Sprite::create("1,1.png");
	sprite->setPosition(Vec2(DESIGN_SCREEN_WIDTH/2, DESIGN_SCREEN_HEIGHT/2));
	sprite->setTag(1111);
	mCurrentLayer = layer;
	layer->addChild(sprite);
}

void HttpServices::hideLoading(bool isSucess)
{
	if (isSucess){
		mCurrentLayer->removeChildByTag(1111);
	}
	else{
		//show network fail message
	}
}

std::string HttpServices::getMethodName(HttpRequestMethod method){
	switch (method)
	{
	case HttpRequestMethod::UPLOAD_MAP: return "uploadMap";
	default:
		break;
	}
}

void HttpServices::returnDelegate(HttpRequestMethod method, Json* jsonResponseData){
	switch (method)
	{
	//case HttpRequestMethod::UPLOAD_MAP: mDelegate->uploadMap("");
	default:
		break;
	}
}
