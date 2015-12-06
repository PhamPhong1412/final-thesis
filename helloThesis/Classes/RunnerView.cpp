#include "RunnerView.h"

bool RunnerView::init(){
	mBody = CSLoader::createNode(FileUtils::getInstance()->fullPathForFilename("mario.csb"));
	mAnimation = CSLoader::createTimeline(FileUtils::getInstance()->fullPathForFilename("mario.csb"));
	mAnimation->setFlags(PlayerState::ON_GROUND);
	mAnimation->play("run", true);
	this->setRotationX(-1);
	mBody->runAction(mAnimation);
	mBody->setPosition(0, 0);
	//mBody->setTag(TAG_OBJECT_PLAYER_BODY);
	this->addChild(mBody);

	return true;
}


void RunnerView::update(float delta){

}

void RunnerView::runOnGround(){
	if (mAnimation->getFlags() != PlayerState::ON_GROUND){
		mAnimation->play("run", true);
		mAnimation->setFlags(PlayerState::ON_GROUND);
	}
}

void RunnerView::runOnAir(){
	if (mAnimation->getFlags() != PlayerState::ON_AIR){
		mAnimation->play("jump", false);
		mAnimation->setFlags(PlayerState::ON_AIR);
	}
}

void RunnerView::setDirection(int dir){
	this->setRotationY(dir*180.0f);
}

