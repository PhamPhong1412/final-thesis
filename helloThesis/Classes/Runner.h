#ifndef __RUNNER_H__
#define __RUNNER_H__

#include "cocos2d.h"
#include "cocostudio\ActionTimeline\CSLoader.h"
#include "cocostudio\ActionTimeline\CCActionTimeline.h"
#include "cocostudio\ActionTimeline\CCActionTimelineCache.h"
#include "b2Node.h"
class Runner : public b2Node
{
private:
	Node* mBody;
	cocostudio::timeline::ActionTimeline* mAnimation;
public:
	virtual bool init();

	CREATE_FUNC(Runner);
	
};

#endif