#include "GroundObject.h"

std::vector<GroundObject*> GroundObject::changeDirectionTiles;
std::string GroundObject::s="1";

GroundObject::GroundObject(float xLoc, float yLoc, std::string tileName, bool isEnd){
	Sprite* sprite = Sprite::create(tileName + ".png");
	this->addChild(sprite);
	this->setTag(TAG_OBJECT_GROUND);

	std::vector<std::string> tTypeObject = Utility::splitString(tileName, ",");
	std::string tType = tTypeObject[1];
	GroundType type;
	if (tType == "1"){
		type = GroundType::NORMAL;
	}
	else{
		type = GroundType::SLOPE;
	}


	b2PhysicsBody *b2PhysicBody = new b2PhysicsBody();
	if (type == GroundType::NORMAL) {
		b2Vec2 verts[] = {
			b2Vec2(-sprite->getContentSize().width / 2, sprite->getContentSize().height / 2),
			b2Vec2(sprite->getContentSize().width / 2, sprite->getContentSize().height / 2)
		};
		b2PhysicBody = b2PhysicsBody::createChain(verts, 2,
			b2PhysicsMaterial(0, 0, 0.5));
		b2PhysicBody->setBodyType(b2_staticBody);
	}
	else if (type == GroundType::SLOPE)
	{
		b2Vec2 verts[] = {
			b2Vec2(sprite->getContentSize().width / 2, sprite->getContentSize().height / 2),
			b2Vec2(-sprite->getContentSize().width / 2, -sprite->getContentSize().height / 2)
		};
		b2PhysicBody = b2PhysicsBody::createChain(verts, 2,
			b2PhysicsMaterial(0, 0, 1));

		b2PhysicBody->setBodyType(b2_staticBody);
	}
	this->setb2PhysicsBody(b2PhysicBody);
	this->setb2Position(xLoc, yLoc + sprite->getContentSize().height / 2);
	this->setPosition(xLoc, yLoc + sprite->getContentSize().height / 2);

	if (isEnd)
		changeDirectionTiles.push_back(this);

	//GroundObject::changeDirectionTiles.push_back(this);
	s = "fdsf";
}

bool GroundObject::isChangeDirTile(Node* testTile){
	for (auto &tile : GroundObject::changeDirectionTiles){
		if (tile->getPosition().x == testTile->getPosition().x&&tile->getPosition().y == testTile->getPosition().y)
			return true;
	}
	return false;
	//return this->isChangeDirectionTile;
}
