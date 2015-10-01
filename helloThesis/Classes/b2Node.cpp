#include "b2Node.h"
#include "b2Layer.h"

b2Node::b2Node() :b2Integration()
{
}

void b2Node::setb2PhysicsBody(b2PhysicsBody* body)
{
	body->setUserData(this);
	_body = body;
}
