#ifndef __BULLET_H__
#define __BULLET_H__

#include "cocos2d.h"

#include "GameConfig.h"

USING_NS_CC;

class Bullet : public Node
{
private:
	int direction;
	//Node* mBody;

	void collideGround();

	float scale;
public:
	virtual bool init();

	Vec2 velocity, targetPoint;

	void update(float delta);


	//Physics event
	void collideBullet();

	CREATE_FUNC(Bullet);

};

#endif