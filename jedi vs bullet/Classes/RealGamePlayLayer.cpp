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

	centralPoint = Vec2(visibleSize.width / 2 , origin.y + 100);

	mAnakin = Anakin::create();
	mAnakin->setAnchorPoint(Vec2(0.5, 0));
	mAnakin->setPosition(centralPoint.x, centralPoint.y);
	mAnakin->setScale((visibleSize.height - 200) / (272 / GameConfig::scale));

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

inline bool intersectAABB(float t1, float t2, float l1, float l2, float b1, float b2, float r1, float r2){
	bool topCheck = t1 < b2;
	bool botCheck = b1 > t2;
	bool leftCheck = l1 > r2;
	bool rightCheck = r1 < l2;

	return !(topCheck || botCheck || leftCheck || rightCheck);
	
}

void RealGamePlayLayer::updateBulletPool(){
	float bulletWidth = 49.0f / 2;
	float bulletHeight = 9.0f / 2;

	Size visibleSize = Director::getInstance()->getVisibleSize();
	centralPoint = Vec2(DESIGN_SCREEN_WIDTH / 2, DESIGN_SCREEN_HEIGHT / 2 - 40);

	float rightTopBoxTop = centralPoint.y + 170;
	float rightTopBoxBot = centralPoint.y;
	float rightTopBoxLeft = centralPoint.x;
	float rightTopBoxRight = centralPoint.x + 130;

	float leftTopBoxTop = centralPoint.y + 170;
	float leftTopBoxBot = centralPoint.y;
	float leftTopBoxLeft = centralPoint.x - 130;
	float leftTopBoxRight = centralPoint.x;

	float leftBotBoxTop = centralPoint.y;
	float leftBotBoxBot = centralPoint.y - 80;
	float leftBotBoxLeft = centralPoint.x - 160;
	float leftBotBoxRight = centralPoint.x;

	float rightBotBoxTop = centralPoint.y;
	float rightBotBoxBot = centralPoint.y - 80;
	float rightBotBoxLeft = centralPoint.x;
	float rightBotBoxRight = centralPoint.x + 160;

	//Color4F color(0, 0, 0.5, 0.5);
	//auto draw_node = DrawNode::create();
	//draw_node->drawRect(Vec2(rightBotBoxLeft, rightBotBoxTop), Vec2(rightBotBoxRight, rightBotBoxBot), color);
	//this->addChild(draw_node);

	if (mAnakin->isAttacking()){
		for (int i = 0; i < this->bulletPool->pool.size(); i++){
			auto bullet = this->bulletPool->pool[i];
			if (mAnakin->direction == bullet->direction){
				bool attacktBullet;

				if (mAnakin->getAttackDir() == 1){
					attacktBullet = intersectAABB(rightTopBoxTop, bullet->getPosition().y + bulletHeight,
						rightTopBoxLeft, bullet->getPosition().x - bulletWidth,
						rightTopBoxBot, bullet->getPosition().y - bulletHeight,
						rightTopBoxRight, bullet->getPosition().x + bulletWidth);
					if (attacktBullet){
						this->bulletPool->removeChild(bullet);
						this->bulletPool->pool.erase(this->bulletPool->pool.begin() + i);
						GameConfig::currentScore += 1.0f;
					}
					continue;
				}

				if (mAnakin->getAttackDir() == 2){
					attacktBullet = intersectAABB(rightBotBoxTop, bullet->getPosition().y + bulletHeight,
						rightBotBoxLeft, bullet->getPosition().x - bulletWidth,
						rightBotBoxBot, bullet->getPosition().y - bulletHeight,
						rightBotBoxRight, bullet->getPosition().x + bulletWidth);
					if (attacktBullet){
						this->bulletPool->removeChild(bullet);
						this->bulletPool->pool.erase(this->bulletPool->pool.begin() + i);
						GameConfig::currentScore += 1.0f;
					}
					continue;
				}

				if (mAnakin->getAttackDir() == 3){
					attacktBullet = intersectAABB(leftTopBoxTop, bullet->getPosition().y + bulletHeight,
						leftTopBoxLeft, bullet->getPosition().x - bulletWidth,
						leftTopBoxBot, bullet->getPosition().y - bulletHeight,
						leftTopBoxRight, bullet->getPosition().x + bulletWidth);
					if (attacktBullet){
						this->bulletPool->removeChild(bullet);
						this->bulletPool->pool.erase(this->bulletPool->pool.begin() + i);
						GameConfig::currentScore += 1.0f;
					}
					continue;
				}

				if (mAnakin->getAttackDir() == 4){
					attacktBullet = intersectAABB(leftBotBoxTop, bullet->getPosition().y + bulletHeight,
						leftBotBoxLeft, bullet->getPosition().x - bulletWidth,
						leftBotBoxBot, bullet->getPosition().y - bulletHeight,
						leftBotBoxRight, bullet->getPosition().x + bulletWidth);
					if (attacktBullet){
						this->bulletPool->removeChild(bullet);
						this->bulletPool->pool.erase(this->bulletPool->pool.begin() + i);
						GameConfig::currentScore += 1.0f;
					}
				}
			}
		}
	}
	for (int i = 0; i < this->bulletPool->pool.size(); i++){
		auto bullet = this->bulletPool->pool[i];


		bool intersectAnakin = std::abs(bullet->targetPoint.x - bullet->getPosition().x)<1.0f;
		if (intersectAnakin){
			mAnakin->goDie();
			this->pauseSchedulerAndActions();
			this->bulletPool->pauseSchedulerAndActions();
		}
	}

}


#pragma region touch event
bool RealGamePlayLayer::onTouchBegan(Touch *touch, Event *event){
	if (!GameConfig::gameFinished){
		this->mAnakin->attack(touch->getLocation().x, touch->getLocation().y);
	}
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

}
#pragma endregion
