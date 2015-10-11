#ifndef _LOGIN_SCENE_H_
#define _LOGIN_SCENE_H_

#include "cocos2d.h"
#include "network\HttpClient.h"
USING_NS_CC;

class LoginScene : public Layer
{
private:
public:

	static cocos2d::Scene* createScene();

	virtual bool init();

	void menuPlayCallback(cocos2d::Ref* pSender);

	CREATE_FUNC(LoginScene);
};

#endif