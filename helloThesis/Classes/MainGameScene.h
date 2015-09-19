#ifndef _MAIN_GAME_SCENE_H_
#define _MAIN_GAME_SCENE_H_

#if ENABLE_PHYSICS_BOX2D_DETECT
#include "../../Box2DTestBed/GLES-Render.h"
#include "Box2D/Box2D.h"
#elif ENABLE_PHYSICS_CHIPMUNK_DETECT
#include "chipmunk.h"
#endif

#include "cocos2d.h"
#include "GameBackgroundLayer.h"
#include "GameMap.h"
USING_NS_CC;

class MainGameScene : public Layer
{
private:
	GameMap* gameMap;
public:

	static cocos2d::Scene* createScene();

	virtual bool init();

	void menuPlayCallback(cocos2d::Ref* pSender);

	CREATE_FUNC(MainGameScene);
};

#endif