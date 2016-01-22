#include "RunnerView.h"

bool RunnerView::init(){
	mBody = CSLoader::createNode(FileUtils::getInstance()->fullPathForFilename("jack.csb"));
	mAnimation = CSLoader::createTimeline(FileUtils::getInstance()->fullPathForFilename("jack.csb"));
	mAnimation->setFlags(PlayerState::ON_GROUND);
	mAnimation->play("run", true);
	this->setRotationX(-1);
	mBody->runAction(mAnimation);
	mBody->setPosition(0, 0);
	mBody->setColor(Color3B(50, 50, 200));
	//mBody->setTag(TAG_OBJECT_PLAYER_BODY);
	this->addChild(mBody);
	this->setScale(0.11f);
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


void RunnerView::freezee(bool isFreezee, float speed){
	if (isFreezee){
		if (!isRollingBack()){
			mAnimation->setTimeSpeed(speed);
			mBody->setColor(Color3B(50, 50, 200));
		}
		
	}
	else{
		mBody->setColor(Color3B(255, 255, 255));
		mAnimation->setTimeSpeed(1.0f);
	}
}

void RunnerView::bomPause(bool isBombarded){
	if (isBombarded){
		mBody->setColor(Color3B(69, 69, 69));
		mAnimation->pause();
	}
	else{
		mBody->setColor(Color3B(255, 255, 255));
		mAnimation->resume();
	}
}


bool RunnerView::isRollingBack(){
	int curFrame = mAnimation->getCurrentFrame();

	return curFrame >= 45 && curFrame <= 145;
}

void RunnerView::rollbackDisappear(){
	mBody->setColor(Color3B(255, 255, 255));
	mAnimation->play("disappear", false);
	//mAnimation->setTimeSpeed(0.05f);
}

void RunnerView::rollbackAppear(){
	mAnimation->play("appear", false);
	//mAnimation->setTimeSpeed(0.05f);
}

int RunnerView::getCurFrame(){
	return mAnimation->getCurrentFrame();
}