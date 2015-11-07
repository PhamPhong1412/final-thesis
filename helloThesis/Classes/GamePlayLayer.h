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
	void onTouchesBegan(const std::vector<Touch*>& touches, Event  *event);
	void onTouchesMoved(const std::vector<Touch*>& touches, Event  *event);
	void onTouchesEnded(const std::vector<Touch*>& touches, Event  *event);
	void onTouchesCancelled(const std::vector<Touch*>& touches, cocos2d::Event  *event);

	//Physics event
	void BeginContact(b2Contact* contact);
	void EndContact(b2Contact* contact);
	void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
	void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);
	Runner* mRunner;
	//CREATE_FUNC(GamePlayLayer);
	//CC_SYNTHESIZE(Runner*, mRunner, Runner);
};

#endif 
