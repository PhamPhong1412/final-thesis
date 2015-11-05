#ifndef __RUNNER_H__
#define __RUNNER_H__

#define NORMAL_JUMP_SPEED 30.0F
#define BOOSTED_JUMP_SPEED 60.0F

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

enum PlayerState{
	ON_GROUND, ON_AIR
};

class Runner : public b2Node
{
private:

	Node* mBody;
	cocostudio::timeline::ActionTimeline* mAnimation;

	void collideGround(b2Node* groundNode, b2Contact* contact);
	void endCollideGround();

	void runNormal();

	PlayerState mState = PlayerState::ON_GROUND;

	int direction; 
	int changeDirectionCooldown;

	int jumpSpeedBoostCharges = 0;

	bool isOnGround();

	float getJumpSpeed();
public:
	virtual bool init();
	
	void jump();

	//Physics event
	void BeginContact(b2Node* node, b2Contact* contact);
	void EndContact(b2Node* node, b2Contact* contact);
	//void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
	//void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);

	CREATE_FUNC(Runner);
	
};

#endif