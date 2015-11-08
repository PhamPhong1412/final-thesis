#ifndef _GAME_PLAY_LAYER_H__
#define _GAME_PLAY_LAYER_H__
#include <iostream>

#include "cocos2d.h"
#include "b2Layer.h"
//#include "Runner.h"
#include "RunnerController.h"
#include "GroundObject.h"
#include "GameConfig.h"
#include "Utility.h"
USING_NS_CC;

class GamePlayLayer : public b2Layer
{
private: 
	std::string mMap;
	Camera* camera;
	Follow* cameraFollow;
	float cameraCounter = 0;
public:
	virtual bool init(std::string map);
	void update(float delta);
	void initTiles();
	void createTiles(float xloc, float yLoc);
	void createSlope(float xLoc, bool direction);
	void addTile(std::string tileName, float xLoc, float yLoc);

	//touches event
	bool onTouchBegan(Touch *touch, Event *event);
	void onTouchMoved(Touch *touch, Event *event);
	void onTouchEnded(Touch *touch, Event *event);
	void onTouchCancelled(Touch *touch, Event *event);

	//Physics event
	void BeginContact(b2Contact* contact);
	void EndContact(b2Contact* contact);
	void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
	void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);
	Runner* mRunner;
	//CREATE_FUNC(GamePlayLayer);
	//CC_SYNTHESIZE(Runner*, mRunner, Runner);

	//CC_SYNTHESIZE(bool, isActive, bool);
};

#endif 
