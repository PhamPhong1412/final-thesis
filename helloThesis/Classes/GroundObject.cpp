#include "GroundObject.h"

//std::vector<GroundObject*> GroundObject::changeDirectionTiles;

GroundObject::GroundObject(float xLoc, float yLoc, std::string tileName){
	bool isEnd = false;
	Sprite* sprite = Sprite::create(tileName + ".png");
	this->addChild(sprite);
	this->setTag(TAG_OBJECT_GROUND);

	std::vector<std::string> tTypeObject = Utility::splitString(tileName, ",");
	std::string tType = tTypeObject[1];
	GroundType type;

	if (tType == "1"){
		type = GroundType::NORMAL;
		createNormalPhysicBody(sprite);
	}
	else if (tType == "2"){
		type = GroundType::SLOPE;
		createSlopePhysicBody(sprite);
	}
	else
	{
		type = GroundType::END;
		createEndlPhysicBody(sprite);
		isEnd = true;
	}


	//if (type == GroundType::NORMAL) {

	//}
	//else if (type == GroundType::SLOPE)
	//{

	//}
	this->setb2Position(xLoc, yLoc + sprite->getContentSize().height / 2);
	this->setPosition(xLoc, yLoc + sprite->getContentSize().height / 2);

	//if (isEnd)
	//	changeDirectionTiles.push_back(this);

}

bool GroundObject::isChangeDirTile(Node* testTile){
	//for (auto &tile : GroundObject::changeDirectionTiles){
	//	if (tile->getPosition().x == testTile->getPosition().x&&tile->getPosition().y == testTile->getPosition().y)
	//		return true;
	//}
	return false;
	//return this->isChangeDirectionTile;
}

void GroundObject::createNormalPhysicBody(Sprite* sprite){
	b2PhysicsBody *b2PhysicBody = new b2PhysicsBody();
	//b2Vec2 verts[] = {
	//	//b2Vec2(-sprite->getContentSize().width / 2, -sprite->getContentSize().height / 2),
	//	b2Vec2((int)-sprite->getContentSize().width / 2, sprite->getContentSize().height / 2),
	//	b2Vec2(sprite->getContentSize().width / 2, sprite->getContentSize().height / 2)
	//	//b2Vec2(sprite->getContentSize().width / 2, -sprite->getContentSize().height / 2)
	//};
	//b2PhysicBody = b2PhysicsBody::createChain(verts, 2,
	//	b2PhysicsMaterial(0, 0, 0.5));

	//b2PhysicBody = b2PhysicsBody::createBox(Size(sprite->getContentSize().width, sprite->getContentSize().height),
	//	b2PhysicsMaterial(0, 0,0.5));

	int num = 4;
	b2Vec2 verts[] = {
		b2Vec2((int)-sprite->getContentSize().width / 2, (int)-sprite->getContentSize().height / 2),
		b2Vec2((int)-sprite->getContentSize().width / 2, (int)sprite->getContentSize().height / 2),
		b2Vec2((int)sprite->getContentSize().width / 2, (int)sprite->getContentSize().height / 2),
		b2Vec2((int)sprite->getContentSize().width / 2, (int)-sprite->getContentSize().height / 2)
		//b2Vec2(32.2f , 35.0f )
	};
	 b2PhysicBody = b2PhysicsBody::createPolygon(verts, num, b2PhysicsMaterial(0, 0.01, 0.2));

	b2PhysicBody->setBodyType(b2_staticBody);
	this->setb2PhysicsBody(b2PhysicBody);
}

void GroundObject::createSlopePhysicBody(Sprite* sprite){
	b2PhysicsBody *b2PhysicBody = new b2PhysicsBody();
	//b2Vec2 verts[] = {
	//	b2Vec2(sprite->getContentSize().width / 2, sprite->getContentSize().height / 2),
	//	b2Vec2(-sprite->getContentSize().width / 2, -sprite->getContentSize().height / 2)
	//};
	//b2PhysicBody = b2PhysicsBody::createChain(verts, 2,
	//	b2PhysicsMaterial(0, 0.1, 1));

	int num = 3;
	b2Vec2 verts[] = {
		b2Vec2(sprite->getContentSize().width / 2, sprite->getContentSize().height / 2),
		b2Vec2(-sprite->getContentSize().width / 2, -sprite->getContentSize().height / 2),
		b2Vec2(sprite->getContentSize().width / 2, -sprite->getContentSize().height / 2)
	};
	 b2PhysicBody = b2PhysicsBody::createPolygon(verts, num, b2PhysicsMaterial(0, 0.1, 0.8));

	b2PhysicBody->setBodyType(b2_staticBody);
	this->setb2PhysicsBody(b2PhysicBody);
}

void GroundObject::createEndlPhysicBody(Sprite* sprite){
	b2PhysicsBody *b2PhysicBody = new b2PhysicsBody();
	b2PhysicBody = b2PhysicsBody::createBox(Size(sprite->getContentSize().width, sprite->getContentSize().height), 
		b2PhysicsMaterial(0, 0, 0.1));

	b2PhysicBody->setBodyType(b2_staticBody);
	this->setb2PhysicsBody(b2PhysicBody);
}