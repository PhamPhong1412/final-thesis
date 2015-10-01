#include "Runner.h"

bool Runner::init(){
	mBody = CSLoader::createNode(FileUtils::getInstance()->fullPathForFilename("mummy.csb"));
	mAnimation = CSLoader::createTimeline(FileUtils::getInstance()->fullPathForFilename("mummy.csb"));
	mAnimation->play("walk", true);
	mBody->runAction(mAnimation);
	mBody->setPosition(0, 0);
	this->addChild(mBody);

	auto b2PhysicBody = b2PhysicsBody::createBox(Size(69, 69), b2PhysicsMaterial(0.5, 0, 1));
	b2PhysicBody->setBodyType(b2_dynamicBody);
	this->setb2PhysicsBody(b2PhysicBody);

	return true;
}




