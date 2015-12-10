#ifndef __BULLET_POOL_H__
#define __BULLET_POOL_H__

#include "cocos2d.h"

#include "GameConfig.h"
#include "Bullet.h"

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

	std::vector<Bullet*> pool;

	void update(float delta);

	CREATE_FUNC(BulletPool);



};

#endif