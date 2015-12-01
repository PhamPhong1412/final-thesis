#ifndef __HTTP_SERVICES_H__
#define __HTTP_SERVICES_H__

#include "cocos2d.h";
#include "network\HttpClient.h";
class HttpServices;

class HttpServicesDelegate
{
public:
	/**
	* @js NA
	* @lua NA
	*/
	virtual ~HttpServicesDelegate() {}
	/**
	* @js NA
	* @lua NA
	*/
	virtual void getUID(std::string uid) {};

};

class HttpServices : public cocos2d::Layer
{
private:
	HttpServicesDelegate *mDelegate;
	Layer *mCurrentLayer;
	void showLoading(Layer *layer);
	void hideLoading();
public:
    static cocos2d::Scene* createScene();

	void setDelegate(HttpServicesDelegate* pDelegate) { mDelegate = pDelegate; }

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
	CREATE_FUNC(HttpServices);

	//Http Response Callback
	void onHttpRequestCompleted(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response, std::string uid);

	void onMenuPostTestClicked(cocos2d::Ref *sender, bool isImmediate, std::string uid);

	void onMenuPostBinaryTestClicked(cocos2d::Ref *sender, bool isImmediate);


	static HttpServices* inst;

private:
	cocos2d::Label* _labelStatusCode;
};

#endif // __HELLOWORLD_SCENE_H__
