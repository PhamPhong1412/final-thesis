#ifndef _REAL_GAME_PLAY_LAYER_H__
#define _REAL_GAME_PLAY_LAYER_H__

#include "cocos2d.h"

#include "b2Layer.h"

#include "QuadNode.h"
#include "RunnerController.h"
#include "GroundObject.h"
#include "RateHUDLayer.h"
#include "HttpServices.h"
#include "GameConfig.h"
USING_NS_CC;

class RealGamePlayLayerDelegate
{
public:
    /**
     * @js NA
     * @lua NA
     */
    virtual ~RealGamePlayLayerDelegate() {}
    /**
     * @js NA
     * @lua NA
     */
    virtual void realUpdateTime(float time) {};
    
};

class RealGamePlayLayer : public b2Layer, public RateHUDLayerDelegate, public HttpServicesDelegate
{
private:
    Layer *mParentLayer;
    RateHUDLayer *rateLayer;
	QuadNode* quadTree;
	std::string mMap;
	Camera* camera;
	Follow* cameraFollow;
    RealGamePlayLayerDelegate *mDelegate;
    
    float time;
	bool mCanRate;
	int quadtreeUpdateCounter = 0;
	//std::vector<ObjectNode>* currentObjectList;
	set<string>* currentObjectList;
	vector<QuadNode*>* currentQuadNode;
	void updateQuadTree();
	HttpShortMapInfo mMapInfo;
public:
	virtual bool init(std::string map, Layer *parentLayer, HttpShortMapInfo mapInfo);
    virtual void exitBack();
    virtual void ratePress(int Number);
    
    
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
    
    void setDelegate(RealGamePlayLayerDelegate* pDelegate) { mDelegate = pDelegate; }

	virtual void rateMap();
	//CREATE_FUNC(GamePlayLayer);
	//CC_SYNTHESIZE(Runner*, mRunner, Runner);

	//CC_SYNTHESIZE(bool, isActive, bool);
};

#endif 
