#ifndef _SNOWFLAKE_
#define _SNOWFLAKE_

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

class SnowFlake : public b2Node
{
private:

	Node* mBody;
	cocostudio::timeline::ActionTimeline* mAnimation;

	
public:
	bool exploded;
	void update(float delta);
	virtual bool init();
	void explode();



	CREATE_FUNC(SnowFlake);
	
};

#endif