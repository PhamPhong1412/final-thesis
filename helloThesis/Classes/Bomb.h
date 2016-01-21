#ifndef _BOMB_
#define _BOMB_

#include "cocos2d.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include <cocostudio/ActionTimeline/CSLoader.h>
#include <cocostudio/ActionTimeline/CCActionTimeline.h>
#include <cocostudio/ActionTimeline/CCActionTimelineCache.h>
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#include "cocostudio\ActionTimeline\CSLoader.h"
#include "cocostudio\ActionTimeline\CCActionTimeline.h"
#include "cocostudio\ActionTimeline\CCActionTimelineCache.h"
#endif

#include "GroundObject.h"

class Bomb : public b2Node
{
private:

	Node* mBody;
	cocostudio::timeline::ActionTimeline* mAnimation;

	
public:
	bool exploded;
	void update(float delta);
	virtual bool init();
	void explode();
	void jump();



	CREATE_FUNC(Bomb);
	
};

#endif