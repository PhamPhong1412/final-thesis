#include "b2Integration.h"
#include "b2Layer.h"

b2Integration::b2Integration()
{
	_body = nullptr;
}

void b2Integration::setb2Transform(float x, float y)
{
	if (_body)
		_body->setb2Transform(x, y);
}

void b2Integration::setb2Transform(float x, float y, float angle)
{
	if (_body)
		_body->setb2Transform(x, y);
}

void b2Integration::setb2TransformX(float x)
{
	if (_body)
		_body->setb2TransformX(x);
}

void b2Integration::setb2TransformY(float y)
{
	if (_body)
		_body->setb2TransformY(y);
}

void b2Integration::setb2TransformAngle(float angle)
{
	if (_body)
		_body->setb2TransformAngle(angle);
}

void b2Integration::setb2Position(float x, float y)
{
	if (_body)
		_body->setb2Position(x, y);
}

void b2Integration::setb2PositionX(float x)
{
	if (_body)
		_body->setb2PositionX(x);
}

void b2Integration::setb2PositionY(float y)
{
	if (_body)
		_body->setb2PositionY(y);
}

void b2Integration::addb2Child(b2Integration* child)
{
	_b2Child.push_back(child);
}

void b2Integration::clearb2Child()
{
	_b2Child.clear();
}

std::vector<b2Integration*> b2Integration::getb2Child()
{
	return _b2Child;
}

void b2Integration::setUserData(void* data)
{ 
	_body->setUserData(data); 
}

Vec2 b2Integration::getb2Position()
{
	if (_body)
		return _body->getb2Position();
	else
		return Vec2(0, 0);
}

void b2Integration::removeSelf()
{
	if (auto node = dynamic_cast<Node*>(this))
	{
		if (auto parent = dynamic_cast<b2Layer*>(node->getParent()))
		{
			parent->removeChild(node);
		}
		else
		{
			node->removeFromParent();
		}
	}
}

void b2Integration::replaceb2PhysicsBody(b2PhysicsBody* body)
{
	body->setb2Position(this->getb2Position().x, this->getb2Position().y);
	if (auto node = dynamic_cast<Node*>(this))
		if (auto layer = dynamic_cast<b2Layer*>(node->getParent()))
		{
			//remove from body from world
			layer->removeb2PhysicsBody(_body);
			//set child new body
			this->setb2PhysicsBody(body);
			//add this child body to world
			layer->addToPhysicsWorld(node);
		}
		else
		{
			//set child new body
			this->setb2PhysicsBody(body);
		}
}