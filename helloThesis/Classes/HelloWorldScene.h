#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
//#include "extensions\cocos-ext.h";
#include "network\HttpClient.h";

class HelloWorld : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

	//Http Response Callback
	void onHttpRequestCompleted(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response);

	void onMenuPostTestClicked(cocos2d::Ref *sender, bool isImmediate);
	void onMenuPostBinaryTestClicked(cocos2d::Ref *sender, bool isImmediate);

private:
	cocos2d::Label* _labelStatusCode;
};

#endif // __HELLOWORLD_SCENE_H__
