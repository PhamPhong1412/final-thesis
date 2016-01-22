#ifndef __RUNNER_MODEL_H__
#define __RUNNER_MODEL_H__

#define NORMAL_JUMP_SPEED 30.0f
#define BOOSTED_JUMP_SPEED 60.0f
#define FREEZEE_TIME 3.0f
#define BOMB_TIME 2.0f

#include "b2Node.h"

enum PlayerState{
	ON_GROUND, ON_AIR
};

class RunnerModel : public b2Node
{
private:

	PlayerState mState = PlayerState::ON_GROUND;

	int tag;
	float lastX;
	int direction; 
	int changeDirectionCooldown;

	int jumpSpeedBoostCharges = 0;
	bool isFinish = false;
public:
	float freezeeTime, bombTime;
	bool didRollBacked;

	bool isMultiJump = false;
	virtual bool init();

	PlayerState getState();
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

	void update(float delta);

	CREATE_FUNC(RunnerModel);
	
};

#endif