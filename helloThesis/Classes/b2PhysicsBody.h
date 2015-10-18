#ifndef __B2_PHYSICS_BODY_H__
#define __B2_PHYSICS_BODY_H__

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "Global.h"

USING_NS_CC;

typedef struct b2PhysicsMaterial
{
	float density;          ///< The density of the object.
	float restitution;      ///< The bounciness of the physics body.
	float friction;         ///< The roughness of the surface of a shape.

	b2PhysicsMaterial()
		: density(0.0f)
		, restitution(0.0f)
		, friction(0.0f)
	{}

	b2PhysicsMaterial(float aDensity, float aRestitution, float aFriction)
		: density(aDensity)
		, restitution(aRestitution)
		, friction(aFriction)
	{}
};

class b2PhysicsBody
{
private:
	void setShapeAndMaterial(b2Shape* shape, const b2PhysicsMaterial &material);
protected:
	//init physic shape body
	void initBox(const Size &size, const b2PhysicsMaterial &material);
	void initChain(b2Vec2 * vertices, int32 count, const b2PhysicsMaterial &material);
	void initChain2(const b2Vec2 * vertices, int32 count, const b2PhysicsMaterial &material);
	void initPolygon(b2Vec2 * vertices, int32 count, const b2PhysicsMaterial &material);
	void initPolygon2(const b2Vec2 * vertices, int32 count, const b2PhysicsMaterial &material);
	void initCircle(float radius, const b2PhysicsMaterial &material);
	void initEdgeShape(b2Vec2 v1, b2Vec2 v2, const b2PhysicsMaterial &material);
	void initEdgeShape2(const b2Vec2 v1, const b2Vec2 v2, const b2PhysicsMaterial &material);
public:
	//constructor & destructor
	//default body type is Static body, you can set it to dynamic or kinematic
	b2PhysicsBody();
	~b2PhysicsBody();

	//create a box Body
	static b2PhysicsBody* createBox(const Size &size, const b2PhysicsMaterial &material);
	//Create a chain Body, using normal Position
	static b2PhysicsBody* createChain(b2Vec2 * vertices, int32 count, const b2PhysicsMaterial &material);
	//create a chain Body, using b2 position(normal position / PTM_RATIO)
	static b2PhysicsBody* createChain2(const b2Vec2 * vertices, int32 count, const b2PhysicsMaterial &material);
	//create a polygon Body using normal position
	static b2PhysicsBody* createPolygon(b2Vec2 * vertices, int32 count, const b2PhysicsMaterial &material);
	//create a polygon Body using b2 position(normal position / PTM_RATIO)
	static b2PhysicsBody* createPolygon2(const b2Vec2 * vertices, int32 count, const b2PhysicsMaterial &material);
	//create circle
	static b2PhysicsBody* createCircle(float radius, const b2PhysicsMaterial &material);
	//create Edge Shape,  using normal position
	static b2PhysicsBody* createEdgeShape(b2Vec2 v1, b2Vec2 v2, const b2PhysicsMaterial &material);
	//create Edge Shape,  using b2 position(normal position / PTM_RATIO)
	static b2PhysicsBody* createEdgeShape2(const b2Vec2 v1, const b2Vec2 v2, const b2PhysicsMaterial &material);
	
	//set function
	void setb2Transform(float x, float y);
	void setb2Transform(float x, float y, float angle);
	void setb2TransformX(float x);
	void setb2TransformY(float y);
	void setb2TransformAngle(float angle);
	void setb2TransformY(float x, float y);
	void setb2Position(float x, float y);
	void setb2PositionX(float x);
	void setb2PositionY(float y);
	Vec2 getb2Position();
	void setUserData(void* data){ _bodyDef.userData = data; };
	void setBodyType(b2BodyType bodyType);


	//body's properties
	CC_SYNTHESIZE(b2Body*,_body, Body);
	CC_SYNTHESIZE(b2BodyDef, _bodyDef, BodyDef);
	CC_SYNTHESIZE(b2FixtureDef, _shapeDef, ShapeDef);
};

#endif