#include "RealGamePlayLayer.h"

// on "init" you need to initialize your instance
bool RealGamePlayLayer::init(std::string map)
{
	if (!Layer::init())
	{
		//		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 centralPoint = Vec2(visibleSize.width / 2, visibleSize.height / 2);
	mAnakin = Anakin::create();
	mAnakin->setPosition(centralPoint.x-10, centralPoint.y);
	this->addChild(mAnakin);

	auto listener = EventListenerTouchOneByOne::create();

	listener->onTouchBegan = CC_CALLBACK_2(RealGamePlayLayer::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(RealGamePlayLayer::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(RealGamePlayLayer::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	this->scheduleUpdate();

	this->setTag(TAG_NORMAL_LAYER);
	return true;
}

void RealGamePlayLayer::update(float delta){

}



#pragma region touch event
bool RealGamePlayLayer::onTouchBegan(Touch *touch, Event *event){
	this->mAnakin->attack(touch->getLocation().x, touch->getLocation().y);
	return true;
}

void RealGamePlayLayer::onTouchMoved(Touch *touch, Event *event)
{

}

void RealGamePlayLayer::onTouchEnded(Touch *touch, Event *event)
{

}

void RealGamePlayLayer::onTouchCancelled(Touch *touch, Event *event)
{
	//this->mRunner->getb2PhysicsBody()->getBody()->SetLinearVelocity(b2Vec2(20.0f, 0));

}
#pragma endregion