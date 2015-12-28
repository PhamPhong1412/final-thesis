#include "HttpServices.h"

HttpServices* HttpServices::inst = new HttpServices();

inline bool HttpServices::checkValid(bool ex, HttpRequestMethod method){
	if (!ex){
		hideLoading(false,method);
		return true;
	}
else
	return false;
}
void HttpServices::onHttpRequestCompleted(HttpClient *sender, HttpResponse *response, HttpRequestMethod method)
{

	std::vector<char> *buffer = response->getResponseData();	
	if (checkValid((buffer->size() != 0),method)){
		return;
	}

	char * concatenated = (char *)malloc(buffer->size() + 1);
	std::string s2(buffer->begin(), buffer->end());
	Utility::strcpy(concatenated, s2.c_str());

	Json * json = Json_create(concatenated);
	if (checkValid((json != nullptr),method)){
		return;
	}
	CC_SAFE_DELETE(concatenated);
	json = Json_getItem(json, "data");
	const char * result = Json_getString(json, "result", "fail");

	if (checkValid((result != "fail"),method)){
		return;
	}

	const char * test2 = Json_getString(json, "time_server", "default");

	std::map<std::string, std::string> res;

	Json *c = json->child;
	while (c){
		res[c->name] = c->valueString;
		c = c->next;
	}
	returnDelegate(method, res);
	//mDelegate->getUID("phong khung");

	hideLoading(true, method);
}

void HttpServices::sendRequest(cocos2d::Ref *sender, std::vector<HttpRequestParameter> RequestParameter, HttpRequestMethod method, bool isImmediate)
{
	showLoading((Layer*)sender);

	HttpRequest* request = new (std::nothrow) HttpRequest();
	request->setUrl("192.168.1.74:9999/runner");
	request->setRequestType(HttpRequest::Type::POST);
	request->setResponseCallback(CC_CALLBACK_2(HttpServices::onHttpRequestCompleted, this, method));

	// write the post data
	std::string methodName = getMethodName(method);
	std::string phoneID = Utility::getPhoneID();

	RequestParameter.push_back(HttpRequestParameter("method", methodName));
	RequestParameter.push_back(HttpRequestParameter("phone_id", phoneID));
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
	mCurrentLayer = layer;
	mLoadingHUD = new LoadingHUDLayer(layer);
	layer->addChild(mLoadingHUD);
}

void HttpServices::hideLoading(bool isSucess, HttpRequestMethod method)
{
	if (isSucess){
		switch (method)
		{
		case HttpRequestMethod::UPLOAD_MAP:
			MessageBox("Upload map sucess", "Sucess");
		default:
			break;
		}
		mLoadingHUD->exitLoading();
	}
	else{
		//show network fail message
		switch (method)
		{
		case HttpRequestMethod::UPLOAD_MAP: 
			MessageBox("Cant up load map", "Failed");
		default:
			break;
		}
		
		mLoadingHUD->exitLoading();
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

void HttpServices::returnDelegate(HttpRequestMethod method, std::map<std::string, std::string> response){
	switch (method)
	{
	case HttpRequestMethod::UPLOAD_MAP: mDelegate->uploadMap();
	default:
		break;
	}
}
