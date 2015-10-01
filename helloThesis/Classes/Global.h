#ifndef __GLOBAL_H__
#define __GLOBAL_H__

#include "cocos2d.h"

#define PTM_RATIO 32
#define SET_DEBUG 1

#define SCREEN_WIDTH		800
#define SCREEN_HEIGHT		480

#define TAG_ACTION_MOVING	0
#define TAG_ACTION_JUMP		1

#define TAG_OBJECT_PLAYER	1
#define TAG_OBJECT_GROUND	2
#define TAG_OBJECT_MAP		3

#define MOVING_DIRECTION_LEFT	-1
#define MOVING_DIRECTION_RIGHT	1
#define MOVING_DIRECTION_NO		0


USING_NS_CC;

class Global
{
private:
	static bool instanceFlag;
	static Global* _global;
public:
	Global();
	~Global(){ instanceFlag = false; };
	static Global* getInstance();

	CC_SYNTHESIZE(float, _mapWidth, MapWidth);
	CC_SYNTHESIZE(float, _mapHeight, MapHeight);
	CC_SYNTHESIZE(bool, _pause, Pause);
	CC_SYNTHESIZE(Node*, _player, Player);
};

#endif // !_GLOBAL_H_
