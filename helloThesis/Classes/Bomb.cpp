#include "Bomb.h"

bool Bomb::init(){
	mBody = CSLoader::createNode(FileUtils::getInstance()->fullPathForFilename("explosion.csb"));
	mAnimation = CSLoader::createTimeline(FileUtils::getInstance()->fullPathForFilename("explosion.csb"));
	mAnimation->play("normal", true);
	mBody->runAction(mAnimation);
	mBody->setPosition(0, 0);
	this->addChild(mBody);

	exploded = false;
	this->scheduleUpdate();
	this->setScale(0.233333f);
	//this->autorelease();
	return true;
}

void Bomb::update(float delta){
	if (exploded){
		if (mAnimation->getCurrentFrame() == 22){

			this->removeAllChildren();
			this->pauseSchedulerAndActions();
		}
	}
}

void Bomb::explode(){
	exploded = true;
	mAnimation->play("explode", false);
}