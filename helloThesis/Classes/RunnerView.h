#ifndef __RUNNER_VIEW_H__
#define __RUNNER_VIEW_H__

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

#include "RunnerModel.h"

USING_NS_CC;

class RunnerView : public Node
{
private:

	Node* mBody;
	cocostudio::timeline::ActionTimeline* mAnimation;


public:
	void runOnGround();
	void runOnAir();
	void jump();
	void setDirection(int dir);

	virtual bool init();

	void update(float delta);
	
	void freezee(bool isFreezee, float speed);
	CREATE_FUNC(RunnerView);
	void bomPause(bool isBombarded);
	
};

#endif