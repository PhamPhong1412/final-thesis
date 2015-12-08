#include "Anakin.h"

bool Anakin::init(){
	mBody = CSLoader::createNode(FileUtils::getInstance()->fullPathForFilename("anakin.csb"));
	mAnimation = CSLoader::createTimeline(FileUtils::getInstance()->fullPathForFilename("anakin.csb"));
	mAnimation->play("hit", true);
	//mAnimation->setTimeSpeed(0.5f);
	mBody->runAction(mAnimation);
	mBody->setPosition(0, 0);
	mBody->setTag(56);
	this->addChild(mBody);
	direction = 1;

	Size visibleSize = Director::getInstance()->getVisibleSize();
	centralPoint = Vec2(visibleSize.width / 2, visibleSize.height / 2);

	float designH = DESIGN_SCREEN_HEIGHT - 100;
	float curH = visibleSize.height - 100;
	float defaulScale = (visibleSize.height - 100)/68;
	mBody->setScale(1);



	this->setTag(55);

	this->direction = 1;
	this->scheduleUpdate();
	return true;
}

void Anakin::update(float delta){
	int curFrame = mAnimation->getCurrentFrame();
	
	if (curFrame == 40 || curFrame == 20){
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

	if (xLoc > centralPoint.x&&direction!=1){
		mBody->setRotationY(0);
		this->setPosition(Vec2(this->getPosition().x + 20, this->getPosition().y));
		direction = 1;
	}
	if (xLoc < centralPoint.x&&direction == 1){
		mBody->setRotationY(180);
		this->setPosition(Vec2(this->getPosition().x - 20, this->getPosition().y));
		direction = -1;
	}
	//else{
	//	mBody->setRotationY(180);
	//	this->setPosition(Vec2(this->getPosition().x - 20, this->getPosition().y)) ;
	//}

	if (yLoc > centralPoint.y){
		mAnimation->play("hit", false);
	}
	else{
		mAnimation->play("hit2", false);
	}
}