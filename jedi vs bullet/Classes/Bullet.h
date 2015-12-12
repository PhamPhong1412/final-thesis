#ifndef _BULLET_H_
#define _BULLET_H_

#include "cocos2d.h"

#include "GameConfig.h"
USING_NS_CC;
class Bullet : public Node{

public :
	virtual bool init();
	int direction;
	Vec2 targetPoint;
	int attackEdge;

	CREATE_FUNC(Bullet);

	void update(float delta);
	void collideBullet();
};

#endif
