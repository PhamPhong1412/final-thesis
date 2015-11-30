#ifndef _REAL_GAME_PLAY_LAYER_H__
#define _REAL_GAME_PLAY_LAYER_H__

#include "cocos2d.h"
#include "b2Layer.h"
#include "QuadNode.h"
#include "RunnerController.h"
#include "GroundObject.h"
#include "GameConfig.h"
USING_NS_CC;

class RealGamePlayLayer : public b2Layer
{
private:
	QuadNode* quadTree;
	std::string mMap;
	Camera* camera;
	Follow* cameraFollow;

	int quadtreeUpdateCounter = 0;
	//std::vector<ObjectNode>* currentObjectList;
	set<string>* currentObjectList;
	vector<QuadNode*>* currentQuadNode;
	void updateQuadTree();
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
