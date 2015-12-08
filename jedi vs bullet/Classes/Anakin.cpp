#include "Anakin.h"

bool Anakin::init(){
	mBody = CSLoader::createNode(FileUtils::getInstance()->fullPathForFilename("anakin.csb"));
	mAnimation = CSLoader::createTimeline(FileUtils::getInstance()->fullPathForFilename("anakin.csb"));
	mAnimation->play("hit", true);
	mBody->runAction(mAnimation);
	mBody->setPosition(0, 0);
	mBody->setTag(56);
	this->addChild(mBody);

	

	this->setTag(55);

	this->direction = 1;
	return true;
}

void Anakin::collideBullet(){

}

void Anakin::play(){

	mAnimation->play("hit2", false);
}