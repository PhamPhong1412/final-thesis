#include "Runner.h"

bool Runner::init(){
	mBody = CSLoader::createNode(FileUtils::getInstance()->fullPathForFilename("mummy.csb"));
	mAnimation = CSLoader::createTimeline(FileUtils::getInstance()->fullPathForFilename("mummy.csb"));
	mAnimation->play("walk", true);
	mBody->runAction(mAnimation);
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

	//auto b2PhysicBody = b2PhysicsBody::createPolygon(verts, num, b2PhysicsMaterial(0.5, 0, 1));
	auto b2PhysicBody = b2PhysicsBody::createBox(Size(20,50), b2PhysicsMaterial(0, 0, 0.1));
	b2PhysicBody->setBodyType(b2_dynamicBody);
	this->setb2PhysicsBody(b2PhysicBody);

	this->setTag(TAG_OBJECT_PLAYER);
	return true;
}

void Runner::updateCollision(Node* node, b2Contact* contact){
	int targetTag = node->getTag();
	switch (targetTag)
	{
	case TAG_OBJECT_GROUND:{
							   this->collideGround(node, contact);
							   break;
	}
	default:
		break;
	}
}

void Runner::collideGround(Node* groundNode, b2Contact* contact){
	//for (int i = 0; i < contact->GetManifold()->pointCount; i++) {
	//	float x=contact->GetManifold()->points[i].localPoint.x;
	//	float y = contact->GetManifold()->points[i].localPoint.y;
	//}

	float tileSize = 70 / GameConfig::scale;
	float yGround = groundNode->getPosition().y;
	float hGround = yGround + tileSize/2;

	float hRunner = this->getPosition().y -45 /(2*GameConfig::scale);
	float hB2y = this->getb2Position().y;
	float hb2 = this->getb2Position().y - 50 / 2;

	//float hmRunner = this->mBody->getBoundingBox().getMaxY();
	int y = this->getPosition().y;
	float vy = this->getb2PhysicsBody()->getVelocityY();
	//if (hb2<hGround){
	if (this->getb2PhysicsBody()->getVelocityY()>15.0f){
		//one way platform
		contact->SetEnabled(false);
	}
	else{
		this->getb2PhysicsBody()->setVelocityX(15.0f);
		//contact->SetEnabled(false);
	}
}
