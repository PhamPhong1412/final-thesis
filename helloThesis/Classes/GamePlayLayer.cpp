#include "GamePlayLayer.h"

// on "init" you need to initialize your instance
bool GamePlayLayer::init(std::string map)
{
	if (!b2Layer::init())
	{
//		return false;
	}
	
	Size visibleSize = Director::getInstance()->getVisibleSize();
	this->mMap = map;
	mRunner = Runner::create();
	mRunner->mModel->setb2Position(100, 300);
	mRunner->setPosition(100, 300);
	this->addChild(mRunner);

	std::vector<std::string> part = Utility::splitString(map, "dm");

	std::vector<std::string> widthHeight = Utility::splitString(part.at(0), "\n");
	int nTilesWidth = std::stoi(widthHeight.at(0));
	int nTilesHeight = std::stoi(widthHeight.at(1));

	float x, y;
	float tileSize = 70 / GameConfig::scale;
	std::vector<std::string> objectData = Utility::splitString(part.at(1), "\n");
	for (int i = 0; i < nTilesHeight; i++){
		y = (int)(nTilesHeight - i - 1) * tileSize;
		int tmp = y;
		y = tmp;
		std::vector<std::string> currentLineData = Utility::splitString(objectData.at(i), ";");
		for (int j = 0; j < nTilesWidth; j++){
			std::string tileName = currentLineData.at(j);
			if (tileName == "0")
				continue;
			x = j * tileSize ;
			addTile(tileName, x, y);
		}
	}

	auto listener = EventListenerTouchOneByOne::create();

	listener->onTouchBegan = CC_CALLBACK_2(GamePlayLayer::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(GamePlayLayer::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(GamePlayLayer::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	this->scheduleUpdate();
	this->runAction(cocos2d::Follow::create(mRunner, Rect(0, 0, nTilesWidth * 70 / GameConfig::scale,
		nTilesHeight * 70 / GameConfig::scale)));

	this->setTag(TAG_NORMAL_LAYER);

	return true;
}

void GamePlayLayer::update(float delta){

	b2Layer::update(delta);
}

void GamePlayLayer::addTile(std::string tileName, float xLoc, float yLoc){
    if (tileName == "0")
        return;

	GroundObject* go = new GroundObject(xLoc, yLoc, tileName);
	//go->init();

    /*Sprite* sprite = Sprite::create(tileName + ".png");
    b2Node* b2Tiles = b2Node::create();
    b2Tiles->setTag(TAG_OBJECT_GROUND);
    b2Tiles->addChild(sprite);
    std::string tType = tTypeObject[1];
    
    b2PhysicsBody *b2PhysicBody;
    
    if (tType == "1") {
        b2Vec2 verts[] = {
            b2Vec2(-sprite->getContentSize().width / 2, sprite->getContentSize().height / 2),
            b2Vec2(sprite->getContentSize().width / 2, sprite->getContentSize().height / 2)
        };
        b2PhysicBody = b2PhysicsBody::createChain(verts, 2,
                                                       b2PhysicsMaterial(0, 0, 0.5));
        b2PhysicBody->setBodyType(b2_staticBody);
        b2Tiles->setb2PhysicsBody(b2PhysicBody);
        b2Tiles->setPosition(xLoc, yLoc + sprite->getContentSize().height / 2);
        b2Tiles->setb2Position(xLoc, yLoc + sprite->getContentSize().height / 2);
    }
    else if(tType == "2")
    {
        b2Vec2 verts[] = {
            b2Vec2(sprite->getContentSize().width / 2, sprite->getContentSize().height / 2),
            b2Vec2(-sprite->getContentSize().width / 2, -sprite->getContentSize().height / 2)
        };
        b2PhysicBody = b2PhysicsBody::createChain(verts, 2,
                                                       b2PhysicsMaterial(0, 0, 1));
        
        b2PhysicBody->setBodyType(b2_staticBody);
        b2Tiles->setb2PhysicsBody(b2PhysicBody);
        b2Tiles->setPosition(xLoc ,  yLoc + sprite->getContentSize().height / 2);
        b2Tiles->setb2Position(xLoc , yLoc + sprite->getContentSize().height / 2);
    }*/

	this->addChild(go);
}

#pragma region touch event
bool GamePlayLayer::onTouchBegan(Touch *touch, Event *event){
	this->mRunner->jump();
	return true;
}

void GamePlayLayer::onTouchMoved(Touch *touch, Event *event)
{

}

void GamePlayLayer::onTouchEnded(Touch *touch, Event *event)
{

}

void GamePlayLayer::onTouchCancelled(Touch *touch, Event *event)
{
	//this->mRunner->getb2PhysicsBody()->getBody()->SetLinearVelocity(b2Vec2(20.0f, 0));

}
#pragma endregion

#pragma region collision and response

void GamePlayLayer::BeginContact(b2Contact* contact)
{
	auto nodeA = (b2Node*)contact->GetFixtureA()->GetBody()->GetUserData();
	auto nodeB = (b2Node*)contact->GetFixtureB()->GetBody()->GetUserData();

	if (nodeA && nodeB)
	{
		int aTag = nodeA->getTag();
		int bTag = nodeB->getTag();

		if (aTag == TAG_OBJECT_PLAYER)
		{
			this->mRunner->BeginContact(nodeB, contact);

		}
		else
		{
			if (bTag == TAG_OBJECT_PLAYER)
			{
				this->mRunner->BeginContact(nodeA, contact);

			}
		}
	}
}

void GamePlayLayer::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{
	this->BeginContact(contact);
	//return true;
}

void GamePlayLayer::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
{
	this->BeginContact(contact);
}

void GamePlayLayer::EndContact(b2Contact* contact)
{
	auto nodeA = (b2Node*)contact->GetFixtureA()->GetBody()->GetUserData();
	auto nodeB = (b2Node*)contact->GetFixtureB()->GetBody()->GetUserData();

	if (nodeA && nodeB)
	{
		int aTag = nodeA->getTag();
		int bTag = nodeB->getTag();

		if (aTag == TAG_OBJECT_PLAYER)
		{
			this->mRunner->EndContact(nodeB, contact);

		}
		else
		{
			if (bTag == TAG_OBJECT_PLAYER)
			{
				this->mRunner->EndContact(nodeA, contact);

			}
		}
	}
}

#pragma endregion
