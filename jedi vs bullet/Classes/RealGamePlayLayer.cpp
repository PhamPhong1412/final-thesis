#include "RealGamePlayLayer.h"

// on "init" you need to initialize your instance
bool RealGamePlayLayer::init(std::string map)
{
	if (!LayerColor::initWithColor(Color4B(255,255,255,255)))
	{
		//		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	centralPoint = Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
	centralPoint = Vec2(visibleSize.width / 2, visibleSize.height / 2);
	mAnakin = Anakin::create();
	float scale = ((visibleSize.height - 50) / 2) / (50 / GameConfig::scale);
	//mAnakin->setAnchorPoint(Vec2(0.5, 0.5));
	mAnakin->setPosition(centralPoint.x + 20*scale, centralPoint.y + 10*scale);
	this->addChild(mAnakin);

	this->addChild(BulletPool::create());

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