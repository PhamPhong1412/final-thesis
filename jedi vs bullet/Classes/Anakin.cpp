#include "Anakin.h"
#include "GameConfig.h"

bool Anakin::init(){
	Size visibleSize = Director::getInstance()->getVisibleSize();

	mBody = CSLoader::createNode(FileUtils::getInstance()->fullPathForFilename("anakin.csb"));
	mAnimation = CSLoader::createTimeline(FileUtils::getInstance()->fullPathForFilename("anakin.csb"));
	float dm = mBody->getContentSize().width;
	centralPoint = Vec2(visibleSize.width/2, visibleSize.height / 2);
	mAnimation->play("hit", true);
	mBody->runAction(mAnimation);
	mBody->setPosition(0, 0);
	mBody->setTag(56);
	scale = ((visibleSize.height - 50)/2) / (50 / GameConfig::scale);
	//scale *= 1.1;
	//mBody->setScale(scale);
	this->addChild(mBody);

	this->setTag(55);

	this->direction = 1;
	this->direction = 1;
	this->scheduleUpdate();
	return true;
}

void Anakin::update(float delta){

	int curFrame = mAnimation->getCurrentFrame();

	if (curFrame == 40 || curFrame == 20){
		mAnimation->play("idle", true);
		mAnimation->setTimeSpeed(0.583f);
	}
}

void Anakin::collideBullet(){

}

void Anakin::play(){
	int i = mAnimation->getCurrentFrame();
	mAnimation->play("hit2", false);
}

bool Anakin::canAttack(){
	int i = mAnimation->getCurrentFrame();
	return i >= 40 && i <= 60;
}

void Anakin::attack(float xLoc, float yLoc){
	if (!canAttack())
		return;
	scale = 1;
	float x = this->getPosition().x;
	if (xLoc > centralPoint.x&&direction != 1){
		mBody->setRotationY(0);
		this->setPosition(Vec2(this->getPosition().x + 280 * scale, this->getPosition().y));
		direction = 1;
	}
	if (xLoc < centralPoint.x&&direction == 1){
		mBody->setRotationY(180);
		this->setPosition(Vec2(this->getPosition().x - 280 * scale, this->getPosition().y));
		direction = -1;
	}
	//else{
	//	mBody->setRotationY(180);
	//	this->setPosition(Vec2(this->getPosition().x - 20, this->getPosition().y)) ;
	//}
	float newX = this->getPosition().x;
	if (yLoc > centralPoint.y){
		mAnimation->play("hit", false);
	}
	else{
		mAnimation->play("hit2", false);
	}

	mAnimation->setTimeSpeed(1);
}