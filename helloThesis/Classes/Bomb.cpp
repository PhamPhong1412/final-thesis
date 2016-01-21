#include "Bomb.h"

bool Bomb::init(){
	mBody = CSLoader::createNode(FileUtils::getInstance()->fullPathForFilename("explosion.csb"));
	mAnimation = CSLoader::createTimeline(FileUtils::getInstance()->fullPathForFilename("explosion.csb"));
	mAnimation->play("normal", false);
	mBody->runAction(mAnimation);
	mBody->setPosition(0, 0);
	this->addChild(mBody);

	exploded = false;
	this->scheduleUpdate();
	//this->autorelease();
	return true;
}

void Bomb::update(float delta){
	if (exploded){
		if (mAnimation->getCurrentFrame() == 44){
			this->removeAllChildren();
			this->pauseSchedulerAndActions();
		}
	}
}

void Bomb::explode(){
	exploded = true;
	mAnimation->play("explode", false);
}