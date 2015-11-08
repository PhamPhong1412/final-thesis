#include "RunnerModel.h"

bool RunnerModel::init(){
	//int num = 3;
	//b2Vec2 verts[] = {
	//	b2Vec2(0.0f, 40.8f),
	//	b2Vec2(-42.2f , 35.0f ),
	//	//b2Vec2(-20.0f , -40.0f ),
	//	//b2Vec2(20.0f , -40.0f ),
	//	b2Vec2(32.2f , 35.0f )
	//};
    
//	int num = 6;
//	b2Vec2 verts[] = {
//		b2Vec2(20, 50),
//		b2Vec2(0, 50),
//		b2Vec2(0, 20/3),
//		b2Vec2(20 / 3, 0),
//		b2Vec2(20*2/3, 0 ),
//		b2Vec2(20 , 20/3 +2.5)
//		//b2Vec2(32.2f , 35.0f )
//	};
//
//	auto b2PhysicBody = b2PhysicsBody::createPolygon(verts, num, b2PhysicsMaterial(0, 0, 0.1));
	auto b2PhysicBody = b2PhysicsBody::createBox(Size(20,50), b2PhysicsMaterial(0, 0, 0));
    
	b2PhysicBody->setBodyType(b2_dynamicBody);
	this->setb2PhysicsBody(b2PhysicBody);

	this->tag = TAG_OBJECT_PLAYER;

	this->direction = 1;
	this->changeDirectionCooldown = 1;
	return true;
}


bool RunnerModel::isOnGround(){
	bool statusCheck = this->mState == PlayerState::ON_GROUND ? true : false;
	//bool velocityCheck = this->getb2PhysicsBody()->getVelocityY() > -0.5f && this->getb2PhysicsBody()->getVelocityY() < 5.0f;
	return statusCheck;
}

float RunnerModel::getJumpSpeed(){
	if (jumpSpeedBoostCharges > 0){
		jumpSpeedBoostCharges--;
		return BOOSTED_JUMP_SPEED;
	}
	else{
		return NORMAL_JUMP_SPEED;
	}
}

void RunnerModel::setState(PlayerState state){
	this->mState = state;
}

float RunnerModel::getVelocityX(){
	return this->getb2PhysicsBody()->getVelocityX();
}

float RunnerModel::getVelocityY(){
	return this->getb2PhysicsBody()->getVelocityY();
}

void RunnerModel::setVelocityX(float value){
	this->getb2PhysicsBody()->setVelocityX(value);
}

void RunnerModel::setVelocityY(float value){
	this->getb2PhysicsBody()->setVelocityY(value);
}

float RunnerModel::getPosX(){
	return this->getPosition().x;
}

float RunnerModel::getPosY(){
	return this->getPosition().y;
}