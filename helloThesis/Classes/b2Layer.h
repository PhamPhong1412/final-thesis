#ifndef __PHYSICS_LAYER_H__
#define __PHYSICS_LAYER_H__

#include "cocos2d.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

#include <external/Box2D/Box2D.h>

#elif (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)

#include "Box2D\Box2D.h"

#endif
#include "GLES-Render.h"
#include "Global.h"
#include "AnimatedSprite.h"
#include "b2Integration.h"
#include <unordered_set>

USING_NS_CC;

class b2Layer : public Layer, public b2ContactListener
{
private:
	//debug watching properties
	GLESDebugDraw* _debugDraw;
	Mat4 _modelViewMV;
	CustomCommand customCommand;
	//list objects need to be destroyed
	std::unordered_set<b2PhysicsBody*> _onDestroyedObject;

	virtual void onDraw();
	void initPhysicsWorld();

public:
	~b2Layer();
	Node* camera;
	//init b2 layer
	virtual bool init();
	virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) override;

	//update Body and sprite
	void update(float deltatime);

	void stopLayer();
	//add body physics
	void addChild(b2PhysicsBody* child);
	//add a child with its own body
	void addChild(Node* child);

	//this function add child's body to world
	void addToPhysicsWorld(Node* child);

	//abstract collision listener method
	virtual void BeginContact(b2Contact* contact){ };
	virtual void EndContact(b2Contact* contact){ };
	virtual void PreSolve(b2Contact* contact, const b2Manifold* oldManifold){ };
	virtual void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse){ };

	//void destroyChild();
	void removeChild(Node* child, bool cleanup = true);
	void removeb2PhysicsBody(b2PhysicsBody* child);
	CC_SYNTHESIZE(b2World *, _world, World);
};

#endif