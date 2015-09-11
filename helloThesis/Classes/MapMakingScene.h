#ifndef _MAP_MAKING_SCENE_H_
#define _MAP_MAKING_SCENE_H_


#include "cocos2d.h"
USING_NS_CC;

class MapMakingScene : public Layer
{
private:

public:

	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(MapMakingScene);
};

#endif