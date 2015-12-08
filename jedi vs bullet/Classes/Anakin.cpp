#include "Anakin.h"

bool Anakin::init(){
	mBody = CSLoader::createNode(FileUtils::getInstance()->fullPathForFilename("anakin.csb"));
	mAnimation = CSLoader::createTimeline(FileUtils::getInstance()->fullPathForFilename("anakin.csb"));
	mAnimation->play("hit", true);
	mAnimation->setTimeSpeed(0.5f);
	mBody->runAction(mAnimation);
	mBody->setPosition(0, 0);
	mBody->setTag(56);
	this->addChild(mBody);

	Size visibleSize = Director::getInstance()->getVisibleSize();
	centralPoint = Vec2(visibleSize.width / 2, visibleSize.height / 2);

	float designH = DESIGN_SCREEN_HEIGHT - 100;
	float curH = visibleSize.height - 100;
	float defaulScale = 6;
	mBody->setScale(defaulScale);



	this->setTag(55);

	this->direction = 1;
	this->scheduleUpdate();
	return true;
}

void Anakin::update(float delta){
	int curFrame = mAnimation->getCurrentFrame();
	
	if (curFrame == 35 || curFrame == 15){
		mAnimation->play("idle", true);
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

	if (xLoc > centralPoint.x){
		mBody->setRotationY(0);
	}
	else{
		mBody->setRotationY(180);
	}

	if (yLoc > centralPoint.y){
		mAnimation->play("hit", false);
	}
	else{
		mAnimation->play("hit2", false);
	}
}