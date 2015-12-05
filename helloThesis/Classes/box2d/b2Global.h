#ifndef __B2_GLOBAL_H__
#define __B2_GLOBAL_H__

#include "cocos2d.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include <external/Box2D/Box2D.h>
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#include "Box2D\Box2D.h"
#endif

USING_NS_CC;

class b2Global
{
private:
	static b2Global* _b2Global;
protected:
public:
	b2Global();
	static b2Global* getInstance();
	CC_SYNTHESIZE(b2World *, _world, World);
};

#endif