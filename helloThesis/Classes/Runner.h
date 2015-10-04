#ifndef __RUNNER_H__
#define __RUNNER_H__

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

#include "b2Node.h"
class Runner : public b2Node
{
private:
	Node* mBody;
	cocostudio::timeline::ActionTimeline* mAnimation;
public:
	virtual bool init();

	bool onContactBegin(PhysicsContact& contact);

	CREATE_FUNC(Runner);
	
};

#endif