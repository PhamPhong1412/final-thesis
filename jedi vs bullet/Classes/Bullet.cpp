#include "Bullet.h"
#include "GameConfig.h"

bool Bullet::init(){
	Size visibleSize = Director::getInstance()->getVisibleSize();

	auto mBody = Sprite::create("bullet.png");
	velocity = Vec2(0, 0);
	mBody->setPosition(0, 0);
	mBody->setTag(56);
	//scale = ((visibleSize.height - 50)/2) / (50 / GameConfig::scale);
	scale = 1;
	mBody->setScale(scale);
	this->addChild(mBody);

	this->setTag(55);

	this->direction = 1;
	this->scheduleUpdate();

	//return (now.tv_sec * 1000 + now.tv_usec / 1000);

	return true;
}

void Bullet::update(float delta){
	//float x = this->getPosition().x;
	//Vec2 velocity;
	//if (this->getPosition().x > targetPoint.x)
	//	velocity.x = -1;
	//else
	//	velocity.x = 1;

	//if (this->getPosition().x > targetPoint.x)
	//	velocity.x = -1;
	//else
	//	velocity.x = 1;

	//if (this->getPosition().y > targetPoint.y)
	//	velocity.y = -1;
	//else
	//	velocity.y = 1;


	//this->setPosition(Vec2(this->getPosition().x + velocity.x, this->getPosition().y + velocity.y));

}

void Bullet::collideBullet(){

}