#include "GamePlayLayer.h"

// on "init" you need to initialize your instance
bool GamePlayLayer::init()
{
	if (!b2Layer::init())
	{
		return false;
	}
	
	Size visibleSize = Director::getInstance()->getVisibleSize();

	mRunner = Runner::create();
	mRunner->setb2Position(100, 100);
	mRunner->setPosition(100, 100);
	//mRunner->getb2PhysicsBody()->
	this->addChild(mRunner);

	//b2Body *_paddleBody;
	//b2BodyDef paddleBodyDef;
	//paddleBodyDef.type = b2_dynamicBody;
	//paddleBodyDef.position.Set(200, 200);
	//paddleBodyDef.userData = paddle;
	//_paddleBody = _world->CreateBody(&paddleBodyDef);
	this->scheduleUpdate();

	return true;
}

void GamePlayLayer::update(float delta){

	b2Layer::update(delta);

}
