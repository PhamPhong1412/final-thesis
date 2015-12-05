#ifndef __HTTP_SERVICES_H__
#define __HTTP_SERVICES_H__

#include "cocos2d.h"
#include "GameConfig.h"
#include "network\HttpClient.h"
#include "HttpServicesDelegate.h"
#include "Utility.h"
#include "util\json\Json.h"

USING_NS_CC;
using namespace cocos2d::network;


class HttpServices
{
private:
	HttpServicesDelegate* mDelegate;
	Layer* mCurrentLayer;

	void showLoading(Layer* layer);
	void hideLoading(bool isSucess);

	std::string getMethodName(HttpRequestMethod method);

	void returnDelegate(HttpRequestMethod method, Json* jsonResponseData);

	//void deserResponseData(HttpRequestMethod type, std::map<std::string, std::string> response);
public:

	void setDelegate(HttpServicesDelegate* pDelegate) { mDelegate = pDelegate; }

	//Http Response Callback
	void onHttpRequestCompleted(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response, HttpRequestMethod type);

	void sendRequest(cocos2d::Ref *sender, std::vector<HttpRequestParameter> RequestParameter, HttpRequestMethod type, bool isImmediate = false);

	static HttpServices* inst;
};

#endif // __HELLOWORLD_SCENE_H__
