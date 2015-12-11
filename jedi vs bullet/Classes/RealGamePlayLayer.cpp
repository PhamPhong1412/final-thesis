#include "RealGamePlayLayer.h"
// on "init" you need to initialize your instance
bool RealGamePlayLayer::init(std::string map)
{
	if (!LayerColor::initWithColor(Color4B(255, 255, 255, 255)))
	{
		//		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	centralPoint = Vec2(origin.x + visibleSize.width / 2, origin.y + 50);

	mAnakin = Anakin::create();
	//scale = ((visibleSize.height - 50) / 2) / (50 / GameConfig::scale);
	//scale = GameConfig::scale;
	mAnakin->setAnchorPoint(Vec2(0.5, 0));
	mAnakin->setPosition(centralPoint.x, centralPoint.y);
	mAnakin->setScale((visibleSize.height * 4 / 5) / 240);
	this->addChild(mAnakin);
	bulletPool = BulletPool::create();
	this->addChild(bulletPool);

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
	updateBulletPool();
}


void RealGamePlayLayer::updateBulletPool(){
	float bulletWidth = 49.0f / 2;
	float bulletHeight = 9.0f / 2;

	Size visibleSize = Director::getInstance()->getVisibleSize();
	centralPoint = Vec2(visibleSize.width / 2, visibleSize.height / 2);

	float anakinBot;
	float anakinTop;
	float anakinRight;
	float anakinLeft;

	if (this->mAnakin->direction == 1){
		anakinBot = this->mAnakin->getPosition().y - 50 - 60;
		anakinTop = this->mAnakin->getPosition().y + 50 - 60;
		//anakinRight = this->mAnakin->getPosition().x - 100;
		//anakinLeft = this->mAnakin->getPosition().x  - 100;
	}
	else{
		anakinBot = this->mAnakin->getPosition().y - 50 - 60;
		anakinTop = this->mAnakin->getPosition().y + 50 - 60;
		//anakinRight = this->mAnakin->getPosition().x + 120 ;
		//anakinLeft = this->mAnakin->getPosition().x +100;
	}

	//Color4F color(0, 0, 0, 255);
	//auto draw_node = DrawNode::create();

	//if (this->mAnakin->direction == 1){
	//	draw_node->drawRect(Vec2(anakinLeft, anakinTop), Vec2(anakinRight, anakinBot), color);
	//	//draw_node->drawDot(Vec2(anakinRight, anakinBot), 10, color);
	//	this->addChild(draw_node);
	//}

	anakinLeft = centralPoint.x;
	anakinRight = anakinLeft;

	float attackBoxBot = anakinBot - 20;
	float attackBoxTop = anakinTop + 20;
	float attackBoxRight = anakinRight + 90;
	float attackBoxLeft = anakinRight - 90;


	for (int i = 0; i < this->bulletPool->pool.size(); i++){
		auto bullet = this->bulletPool->pool[i];




		bool topCheck = bullet->getPosition().y + bulletHeight < anakinBot;
		bool botCheck = bullet->getPosition().y - bulletHeight > anakinTop;
		bool leftCheck = bullet->getPosition().x - bulletWidth > anakinRight;
		bool rightCheck = bullet->getPosition().x + bulletWidth < anakinLeft;

		bool intersect = !(topCheck || botCheck || leftCheck || rightCheck);
		if (intersect){
			this->bulletPool->removeChild(bullet);
			this->bulletPool->pool.erase(this->bulletPool->pool.begin() + i);
		}
	}
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