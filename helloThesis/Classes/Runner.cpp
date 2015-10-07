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
	auto b2PhysicBody = b2PhysicsBody::createBox(Size(15,40), b2PhysicsMaterial(0, 0, 0.1));
	b2PhysicBody->setBodyType(b2_dynamicBody);
	this->setb2PhysicsBody(b2PhysicBody);

	this->setTag(TAG_OBJECT_PLAYER);

	return true;
}

void Runner::collideGround(Node* groundNode){

}
