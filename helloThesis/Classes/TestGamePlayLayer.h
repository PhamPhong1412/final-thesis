#ifndef _TEST_GAME_PLAY_LAYER_H__
#define _TEST_GAME_PLAY_LAYER_H__

#include "cocos2d.h"

#include "b2Layer.h"

//#include "b2Layer.h"
#include "QuadNode.h"
#include "RunnerController.h"
#include "GroundObject.h"
#include "GameConfig.h"
#include "GameHUDLayer.h"
#include "HttpServices.h"
USING_NS_CC;

class TestGamePlayLayer : public b2Layer, public GameHUDLayerDelegate, public HttpServicesDelegate
{
private:
	GameHUDLayer* chooseLayer;
    Layer *mParentLayer;
	bool mCanUpMap;
	QuadNode* quadTree;
	std::string mMap;
	Camera* camera;
	Follow* cameraFollow;

	float time;
	int quadtreeUpdateCounter = 0;

	
	//std::vector<ObjectNode>* currentObjectList;
	set<string>* currentObjectList;
	vector<QuadNode*>* currentQuadNode;
	void updateQuadTree();
public:
	virtual bool init(std::string map, Layer *parentLayer);

	virtual void uploadMap(std::map<std::string, std::string> response);
	virtual void exitBack();
	virtual void saveMap();
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
