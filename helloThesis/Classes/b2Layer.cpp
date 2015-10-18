#include "b2Layer.h"
#include "b2Global.h"

b2Layer::~b2Layer()
{
	CC_SAFE_DELETE(_world);
}

bool b2Layer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	this->initPhysicsWorld();
	camera = Node::create();

#if (CC_TARGET_PLATFORM != CC_PLATFORM_WP8)
{
}
#endif

}

void b2Layer::addChild(b2PhysicsBody* child)
{
	b2BodyDef t1 = child->getBodyDef();
	child->setBody(_world->CreateBody(&t1));

	b2FixtureDef t2 = child->getShapeDef();
	child->getBody()->CreateFixture(&t2);

}

void b2Layer::addChild(Node* child)
{
	Node::addChild(child);
	this->addToPhysicsWorld(child);
}

void b2Layer::addToPhysicsWorld(Node* child)
{
	if (b2Integration* node = dynamic_cast<b2Integration*>(child))
	{
		if (node->getb2PhysicsBody() != nullptr)
		{
			b2BodyDef t1 = node->getb2PhysicsBody()->getBodyDef();
			node->getb2PhysicsBody()->setBody(_world->CreateBody(&t1));

			b2FixtureDef t2 = node->getb2PhysicsBody()->getShapeDef();
			node->getb2PhysicsBody()->getBody()->CreateFixture(&t2);
		}

		for (int i = 0; i < node->getb2Child().size(); i++)
		{
			if (Node* childnode = dynamic_cast<Node*>(node->getb2Child().at(i)))
				this->addChild(childnode);
		}
	}
}

void b2Layer::initPhysicsWorld()
{
	b2Vec2 gravity;
	gravity.Set(0.0f, -150.0f);
	_world = new b2World(gravity);
	_world->SetContinuousPhysics(true);
	if (SET_DEBUG)
	{
		_debugDraw = new GLESDebugDraw(PTM_RATIO);
		_world->SetDebugDraw(_debugDraw);

		//set debug information display
		uint32 flags = 0;
		flags += b2Draw::e_shapeBit;
		//flags += b2Draw::e_jointBit;
		//flags += b2Draw::e_aabbBit;
		//flags += b2Draw::e_pairBit;
		//flags += b2Draw::e_centerOfMassBit;
		_debugDraw->SetFlags(flags);
	}

	_world->SetContactListener(this);

	b2Global::getInstance()->setWorld(_world);
}

void b2Layer::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
	if (SET_DEBUG)
	{
		GL::enableVertexAttribs(cocos2d::GL::VERTEX_ATTRIB_FLAG_POSITION);
		Director* director = Director::getInstance();
		CCASSERT(nullptr != director, "Director is null when seting matrix stack");
		director->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);

		_modelViewMV = director->getMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);

		customCommand.init(100000);
		customCommand.func = CC_CALLBACK_0(b2Layer::onDraw, this);
		renderer->addCommand(&customCommand);

		director->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
	}
}

void b2Layer::onDraw()
{
	Director* director = Director::getInstance();
	CCASSERT(nullptr != director, "Director is null when seting matrix stack");

	Mat4 oldMV = director->getMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
	director->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, _modelViewMV);
	_world->DrawDebugData();
	director->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, oldMV);
}

void b2Layer::update(float delta)
{
	//destroy objects on queue
	for (std::unordered_set<b2PhysicsBody *>::iterator pos = _onDestroyedObject.begin(); pos != _onDestroyedObject.end(); ++pos)
	{
		if (!_world->IsLocked())
			_world->DestroyBody((*pos)->getBody());
	}
	_onDestroyedObject.clear();

	int velocityIterations = 3;
	int positionIterations = 10;
	_world->Step(delta, velocityIterations, positionIterations);
	for (b2Body* b = _world->GetBodyList(); b; b = b->GetNext())
	{
		if (b->GetUserData() != NULL)
		{
			// Synchronize the AtlasSprites position and rotation with the corresponding body
			CCSprite* myActor = (CCSprite*)b->GetUserData();
			myActor->setPosition(CCPointMake(b->GetPosition().x * PTM_RATIO, b->GetPosition().y * PTM_RATIO));
			myActor->setRotation(-1 * CC_RADIANS_TO_DEGREES(b->GetAngle()));
		}
	}
}

void b2Layer::stopLayer()
{
	this->unscheduleUpdate();
	this->stopAllActions();
	Vector<Node*> allchild = this->getChildren();
	for (int i = 0; i < allchild.size(); i++)
	{
		allchild.at(i)->stopAllActions();
	}
}

void b2Layer::removeChild(Node* child, bool cleanup)
{
	if (auto b2child = dynamic_cast<b2Integration*>(child))
		this->removeb2PhysicsBody(b2child->getb2PhysicsBody());
	Node::removeChild(child, cleanup);
}

void b2Layer::removeb2PhysicsBody(b2PhysicsBody* child)
{
	child->setUserData(NULL);
	_onDestroyedObject.insert(child);
}