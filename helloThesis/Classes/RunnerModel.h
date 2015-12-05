#ifndef __RUNNER_MODEL_H__
#define __RUNNER_MODEL_H__

#define NORMAL_JUMP_SPEED 30.0f
#define BOOSTED_JUMP_SPEED 60.0f

#include "box2d\b2Node.h"
//#include "b2Node.h"

enum PlayerState{
	ON_GROUND, ON_AIR
};

class RunnerModel : public b2Node
{
private:

	PlayerState mState = PlayerState::ON_GROUND;

	int tag;

	int direction; 
	int changeDirectionCooldown;

	int jumpSpeedBoostCharges = 0;
	bool isFinish = false;
public:
	bool isMultiJump = false;
	virtual bool init();

	void setState(PlayerState state);

	bool canJump();
	bool isOnGround();

	float getPosX();
	float getPosY();

	float getVelocityX();
	float getVelocityY();

	void setVelocityX(float value);
	void setVelocityY(float value);

	bool finish();
	void setFinish(bool isFinish);

	void setDirection(int dir);
	int getDirection();
	float getJumpSpeed();
	CREATE_FUNC(RunnerModel);
	
};

#endif