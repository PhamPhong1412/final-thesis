#include "Anakin.h"
#include "GameConfig.h"

bool Anakin::init(){
	Size visibleSize = Director::getInstance()->getVisibleSize();

	mBody = CSLoader::createNode(FileUtils::getInstance()->fullPathForFilename("anakin.csb"));
	mAnimation = CSLoader::createTimeline(FileUtils::getInstance()->fullPathForFilename("anakin.csb"));
	centralPoint = Vec2(visibleSize.width/2, visibleSize.height / 2);
	mAnimation->play("idle", true);
	//mAnimation->play("hit", false);
	//this->mAnimation->play("die", true);
	//mBody->setAnchorPoint(Vec2(0.5, 0));
	mBody->runAction(mAnimation);
	mBody->setPosition(20, 0);
	mBody->setTag(56);
	this->addChild(mBody);

	this->setTag(55);
	this->direction = 1;
	this->scheduleUpdate();
	time = 0;
	return true;
}

float Anakin::anakinXloc;
void Anakin::update(float delta){
	time += delta;
	int curFrame = mAnimation->getCurrentFrame();

	if (curFrame < 140){
		if (direction == 1){
			if (curFrame == 40 || curFrame == 20){
				mAnimation->play("idle", true);
				mAnimation->setTimeSpeed(0.583f);
			}
		}
		else{
			if (curFrame == 90 || curFrame == 110){
				mAnimation->play("idleRevert", true);
				mAnimation->setTimeSpeed(0.583f);
			}
		}
	}
	else{
		if (curFrame == 190)
			GameConfig::gameFinished = true;
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
	if (direction==1){
		return i >= 40 && i <= 60;
	}
	else{
		return i >= 110 && i <= 130;
	}
}

void Anakin::attack(float xLoc, float yLoc){
	if (!canAttack())
		return;
	float x = this->getPosition().x;
	if (xLoc > centralPoint.x&&direction != 1){
		direction = 1;
	}
	if (xLoc < centralPoint.x&&direction == 1){
		direction = -1;
	}
	float newX = this->getPosition().x;
	if (yLoc > centralPoint.y){
		if (direction==1)
			mAnimation->play("hit", false);
		else
			mAnimation->play("hitRevert", false);

	}
	else{
		if (direction == 1)
			mAnimation->play("hit2", false);
		else
			mAnimation->play("hit2Revert", false);
	}

	float attackBoost = GameConfig::currentScore / 200;
	if (attackBoost > 2.0f)
		attackBoost = 2.0f;
	//attackBoost = 2.0f;
	mAnimation->setTimeSpeed(1.1 +  attackBoost);
}

bool Anakin::isAttacking(){
	int curFrame = this->mAnimation->getCurrentFrame();
	bool hitCheck = curFrame > 5 && curFrame < 21;
	bool hit2Check = curFrame > 26 && curFrame < 41;
	bool hitRevertCheck = curFrame > 75 && curFrame < 91;
	bool hitRevert2Check = curFrame > 96 && curFrame < 111;

	return hit2Check || hitCheck || hitRevertCheck || hitRevert2Check;
}

int Anakin::getAttackDir(){
	int curFrame = this->mAnimation->getCurrentFrame();
	bool hitCheck = curFrame > 5 && curFrame < 21;
	bool hit2Check = curFrame > 26 && curFrame < 41;
	bool hitRevertCheck = curFrame > 75 && curFrame < 91;
	bool hitRevert2Check = curFrame > 96 && curFrame < 111;

	if (hitCheck)
		return 1;

	if (hit2Check)
		return 2;

	if (hitRevertCheck)
		return 3;

	if (hitRevert2Check)
		return 4;
	return 1;

}

void Anakin::goDie(){
	this->mAnimation->play("die", false);
	if (direction == -1){
		this->setRotationY(180.0f);
	}
	this->mAnimation->setTimeSpeed(1.0f);
	GameConfig::gameFinished = true;
}