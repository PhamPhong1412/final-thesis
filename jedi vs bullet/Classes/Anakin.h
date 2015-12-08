#ifndef __ANAKIN_H__
#define __ANAKIN_H__

#define NORMAL_JUMP_SPEED 30.0F
#define BOOSTED_JUMP_SPEED 60.0F

#include "cocos2d.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include <cocostudio/ActionTimeline/CSLoader.h>
#include <cocostudio/ActionTimeline/CCActionTimeline.h>
#include <cocostudio/ActionTimeline/CCActionTimelineCache.h>
#else
#include "cocostudio\ActionTimeline\CSLoader.h"
#include "cocostudio\ActionTimeline\CCActionTimeline.h"
#include "cocostudio\ActionTimeline\CCActionTimelineCache.h"
#endif

USING_NS_CC;

enum PlayerState{
	ON_GROUND, ON_AIR
};

class Anakin : public Node
{
private:

	Node* mBody;
	cocostudio::timeline::ActionTimeline* mAnimation;

	void collideGround();


	PlayerState mState = PlayerState::ON_GROUND;

	int direction; 
public:
	virtual bool init();
	void play();
	

	//Physics event
	void collideBullet();

	CREATE_FUNC(Anakin);
	
};

#endif