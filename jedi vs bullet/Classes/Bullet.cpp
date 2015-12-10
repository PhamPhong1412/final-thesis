#include "Bullet.h"
#include "GameConfig.h"

bool Bullet::init(){
	Size visibleSize = Director::getInstance()->getVisibleSize();

	auto mBody = Sprite::create("bullet.png");
	velocity = Vec2(0, 0);
	mBody->setPosition(0, 0);
	mBody->setTag(56);
	//scale = ((visibleSize.height - 50)/2) / (50 / GameConfig::scale);
	//scale = 1;
	//mBody->setScale(scale);
	this->addChild(mBody);

	this->setTag(55);

	this->direction = 1;
	this->scheduleUpdate();

	//return (now.tv_sec * 1000 + now.tv_usec / 1000);

	return true;
}

void Bullet::update(float delta){

}

void Bullet::collideBullet(){

}