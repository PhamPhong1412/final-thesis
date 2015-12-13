#ifndef __BULLET_POOL_H__
#define __BULLET_POOL_H__

#include "cocos2d.h"

#include "GameConfig.h"
#include "Bullet.h"
#include "SoundManager.h"

USING_NS_CC;

class BulletPool : public Node
{
private:
	int direction;
	void collideGround();

	float scale;
	int maxBullet = 6;

	float time, nextShootTime;
	void shootBullet();
public:
	virtual bool init();
	int lastEdge;
	std::vector<Bullet*> pool;

	void update(float delta);

	std::vector<float> shootTime;

	void generateShootPattern();

	CREATE_FUNC(BulletPool);

	void initShootTime();

	std::vector<float> templateSound; // weWillRock U
	std::vector<float> templateSound1; // we will rock u1
	std::vector<float> templateSound2; // we will rock u2
	std::vector<float> templateSound3; // starwar intro
	std::vector<float> templateSound4; // starwar intro
	std::vector<float> templateSound5; // butter fly
	std::vector<float> templateSound6; // butter fly
	std::vector<float> templateSound7; // butter fly
	std::vector<float> templateSound8; // 2ct


};

#endif