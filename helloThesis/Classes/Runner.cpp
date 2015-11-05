#include "Runner.h"

bool Runner::init(){
	mBody = CSLoader::createNode(FileUtils::getInstance()->fullPathForFilename("mummy.csb"));
	mAnimation = CSLoader::createTimeline(FileUtils::getInstance()->fullPathForFilename("mummy.csb"));
	mAnimation->play("walk", true);
	//mBody->runAction(mAnimation);
	mBody->setPosition(0, 0);
	mBody->setTag(TAG_OBJECT_PLAYER_BODY);
	this->addChild(mBody);

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

	this->setTag(TAG_OBJECT_PLAYER);

	this->direction = 1;
	this->changeDirectionCooldown = 1;
	//this->autorelease();
	return true;
}

void Runner::BeginContact(b2Node* node, b2Contact* contact){
//	int targetTag = node->getTag();
//	switch (targetTag)
//	{
//	case TAG_OBJECT_GROUND:{
//							   this->collideGround(node, contact);
//							   break;
//	}
//	default:
//		break;
//	}
    this->collideGround(node, contact);
}

void Runner::collideGround(b2Node* groundNode, b2Contact* contact){
	int groundTag = groundNode->getTag();
	float tmp;
    switch (groundTag)
    	{
            case TAG_OBJECT_GROUND:
            {
					runNormal();
                    break;
            }
            case TAG_OBJECT_BARNORMAL:
            case TAG_OBJECT_BARSLOPE:
            {
                float groundWidth = groundNode->getBoundingBox().getMaxX();
                tmp = 3;
				bool velocityCheck = this->getb2PhysicsBody()->getVelocityY() > tmp;
				bool positionCheck = std::abs(this->getPosition().x - groundNode->getPosition().x) < groundWidth / 2;

				if (velocityCheck && positionCheck){
                        contact->SetEnabled(false);
				}
				else{
					runNormal();
					jumpSpeedBoostCharges++;
				}
                break;
            }
            case TAG_OBJECT_BACK:
            {
                break;
            }
            default:
                break;
    	}
}

void Runner::endCollideGround(){
	this->mState = PlayerState::ON_AIR;
}

bool Runner::isOnGround(){
	bool statusCheck = this->mState == PlayerState::ON_GROUND ? true : false;
	bool velocityCheck = this->getb2PhysicsBody()->getVelocityY() > -0.5f && this->getb2PhysicsBody()->getVelocityY() < 1.0f;
	return statusCheck && velocityCheck;
}

void Runner::EndContact(b2Node* node, b2Contact* contact){
	int targetTag = node->getTag();
	switch (targetTag)
	{
	case TAG_OBJECT_GROUND:{
							   this->endCollideGround();
							   break;
	}
	default:
		break;
	}
}

void Runner::runNormal(){
	this->getb2PhysicsBody()->setVelocityX(10.0f);
	this->mState = PlayerState::ON_GROUND;
}

void Runner::jump(){
	if (this->isOnGround())
		this->getb2PhysicsBody()->setVelocityY(getJumpSpeed());
}

float Runner::getJumpSpeed(){
	if (jumpSpeedBoostCharges > 0){
		jumpSpeedBoostCharges--;
		return BOOSTED_JUMP_SPEED;
	}
	else{
		return NORMAL_JUMP_SPEED;
	}
}
