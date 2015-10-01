#ifndef __B2_INTEGRATION_H__
#define __B2_INTEGRATION_H__

#include "b2PhysicsBody.h"

USING_NS_CC;

class b2Integration
{
private:
	std::vector<b2Integration*> _b2Child;
protected:
public:
	b2Integration();

	void setb2Transform(float x, float y, float angle);
	void setb2Transform(float x, float y);
	void setb2TransformX(float x);
	void setb2TransformY(float y);
	void setb2TransformAngle(float angle);
	void setb2Position(float x, float y);
	void setb2PositionX(float x);
	void setb2PositionY(float y);
	void setUserData(void* data);
	Vec2 getb2Position();

	//b2 child interaction
	void addb2Child(b2Integration* child);
	void clearb2Child();

	virtual void removeSelf();
	std::vector<b2Integration*> getb2Child();

	virtual void replaceb2PhysicsBody(b2PhysicsBody* body);
	CC_SYNTHESIZE(b2PhysicsBody*, _body, b2PhysicsBody);
};

#endif