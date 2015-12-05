#ifndef __B2_NODE_H__
#define __B2_NODE_H__

#include "cocos2d.h"
#include "b2PhysicsBody.h"
#include "b2Integration.h"
USING_NS_CC;

class b2Node :public Node, public b2Integration
{
private:
protected:
public:
	b2Node();
	void setb2PhysicsBody(b2PhysicsBody* body);

	//void replaceb2PhysicsBody(b2PhysicsBody* body);
	CREATE_FUNC(b2Node);
};

enum NodeDirection {
	LEFT, RIGHT
};

#endif