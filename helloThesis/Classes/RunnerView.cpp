#include "RunnerView.h"

bool RunnerView::init(){
	mBody = CSLoader::createNode(FileUtils::getInstance()->fullPathForFilename("mummy.csb"));
	mAnimation = CSLoader::createTimeline(FileUtils::getInstance()->fullPathForFilename("mummy.csb"));
	mAnimation->play("walk", true);
	mBody->runAction(mAnimation);
	mBody->setPosition(0, 0);
	//mBody->setTag(TAG_OBJECT_PLAYER_BODY);
	this->addChild(mBody);

	return true;
}

void RunnerView::runNormal(){
	//this->getb2PhysicsBody()->setVelocityX(10.0f);
	//this->mState = PlayerState::ON_GROUND;
}

