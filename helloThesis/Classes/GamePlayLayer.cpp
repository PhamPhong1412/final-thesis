#include "GamePlayLayer.h"

// on "init" you need to initialize your instance
bool tmp = false;
bool GamePlayLayer::init(std::string map)
{
	if (!b2Layer::init())
	{
//		return false;
	}
	
	Size visibleSize = Director::getInstance()->getVisibleSize();
	this->mMap = map;
	mRunner = Runner::create();
	mRunner->setb2Position(100, 200);
	this->addChild(mRunner);
	mRunner->getb2PhysicsBody()->getBody()->SetLinearVelocity(b2Vec2(0.0f, 0));

	std::vector<std::string> part = Utility::splitString(map, "dm");

	std::vector<std::string> widthHeight = Utility::splitString(part.at(0), "\n");
	int nTilesWidth = std::stoi(widthHeight.at(0));
	int nTilesHeight = std::stoi(widthHeight.at(1));

	float x, y;
	float tileSize = 70 / GameConfig::scale;
	std::vector<std::string> objectData = Utility::splitString(part.at(1), "\n");
	for (int i = 0; i < nTilesHeight; i++){
		y = (nTilesHeight - i - 1) * tileSize;
		std::vector<std::string> currentLineData = Utility::splitString(objectData.at(i), ";");
		for (int j = 0; j < nTilesWidth; j++){
			std::string tileName = currentLineData.at(j);
			if (tileName == "0")
				continue;
			x = j * tileSize;
			addTile(tileName, x, y);
		}
	}
	
	//createTiles(100, 100);
	//createTiles(100, 300);

	auto onTouchListener = EventListenerTouchAllAtOnce::create();
	onTouchListener->onTouchesBegan = CC_CALLBACK_2(GamePlayLayer::onTouchesBegan, this);
	onTouchListener->onTouchesMoved = CC_CALLBACK_2(GamePlayLayer::onTouchesMoved, this);
	onTouchListener->onTouchesEnded = CC_CALLBACK_2(GamePlayLayer::onTouchesEnded, this);
	onTouchListener->onTouchesCancelled = CC_CALLBACK_2(GamePlayLayer::onTouchesCancelled, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(onTouchListener, this);

	this->scheduleUpdate();

	//Rect a = Rect(0, 0, visibleSize.width, visibleSize.height);
	//this->runAction(cocos2d::Follow::create(mRunner, Rect::ZERO));

	return true;
}

void GamePlayLayer::update(float delta){

	b2Layer::update(delta);
	if (tmp){
		this->mRunner->getb2PhysicsBody()->getBody()->SetLinearVelocity(b2Vec2(10.0f, 0));
	}
//	Director::getInstance()->setp
	//mRunner->ve
}

void GamePlayLayer::initTiles(){
	int randValue = 0;
	float currentLocation = 0;
	float currentHeight = 0;
	for (int i = 0; i < 50; i++){
		randValue = random(0, 50);

		if (randValue % 5 == 0){
			if (currentHeight==0){
				createSlope(currentLocation, true);
				currentHeight = 70 * 3 / GameConfig::scale;
			}
			else{
				createSlope(currentLocation, false);
				currentHeight = 0;
			}
			currentLocation += 70 * 3 / GameConfig::scale;
		}
		else{
			i--;
			createTiles(currentLocation, currentHeight);
			currentLocation += 70 / GameConfig::scale;
		}
	}
}

void GamePlayLayer::createTiles(float xLoc, float yLoc){
	Sprite* sprite = Sprite::create("castle.png");
	b2Node* b2Tiles = b2Node::create();
	b2Tiles->setTag(TAG_OBJECT_GROUND);
	b2Tiles->addChild(sprite);

	b2Vec2 verts[] = {
		b2Vec2(-sprite->getContentSize().width / 2, sprite->getContentSize().height / 2),
		b2Vec2(sprite->getContentSize().width / 2, sprite->getContentSize().height / 2)
	};

	auto b2PhysicBody = b2PhysicsBody::createChain(verts, 2,
b2PhysicsMaterial(0, 0, 0.5));
	b2PhysicBody->setBodyType(b2_staticBody);
	b2Tiles->setb2PhysicsBody(b2PhysicBody);
	b2Tiles->setPosition(xLoc, yLoc + sprite->getContentSize().height / 2);
	b2Tiles->setb2Position(xLoc, yLoc + sprite->getContentSize().height / 2);
	this->addChild(b2Tiles);
}

void GamePlayLayer::createSlope(float xLoc, bool direction){
	int dir = direction ? 1 : -1;
	for (int i = 0; i < 3; i++){
		int j = direction ? i : 2 - i; 
		Sprite* sprite = Sprite::create("castleHillLeft.png");
		if (!direction){
			sprite->setFlippedX(true);
		}
		b2Node* b2Tiles = new b2Node();
		b2Tiles->init();
		b2Tiles->setTag(TAG_OBJECT_GROUND);
		b2Tiles->addChild(sprite);

		b2Vec2 verts[] = {
			b2Vec2(dir*sprite->getContentSize().width / 2, sprite->getContentSize().height / 2),
			//b2Vec2(dir*sprite->getContentSize().width / 2, -sprite->getContentSize().height / 2),
			b2Vec2(-dir*sprite->getContentSize().width / 2, -sprite->getContentSize().height / 2)
		};

		auto b2PhysicBody = b2PhysicsBody::createChain(verts, 2, b2PhysicsMaterial(0, 0, 1));
		b2PhysicBody->setBodyType(b2_staticBody);
		b2Tiles->setb2PhysicsBody(b2PhysicBody);
		b2Tiles->setPosition(xLoc + i *sprite->getContentSize().width, 70 / GameConfig::scale + sprite->getContentSize().height / 2 + j *sprite->getContentSize().height);
		b2Tiles->setb2Position(xLoc + i *sprite->getContentSize().width, 70/GameConfig::scale + sprite->getContentSize().height / 2 + j *sprite->getContentSize().height);
		this->addChild(b2Tiles);
	}
	
}

void GamePlayLayer::addTile(std::string tileName, float xLoc, float yLoc){
    if (tileName == "0")
        return;
   
    std::vector<std::string> tTypeObject = Utility::splitString(tileName, ",");
    Sprite* sprite = Sprite::create(tileName + ".png");
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
    }

	this->addChild(b2Tiles);
}

#pragma region touch event
void GamePlayLayer::onTouchesBegan(const std::vector<Touch*>& touches, Event  *event){
	//tmp = !tmp;
	this->mRunner->getb2PhysicsBody()->getBody()->SetLinearVelocity(b2Vec2(0.0f, 100));
}

void GamePlayLayer::onTouchesMoved(const std::vector<Touch*>& touches, cocos2d::Event  *event)
{

}

void GamePlayLayer::onTouchesEnded(const std::vector<Touch*>& touches, cocos2d::Event  *event)
{

}

void GamePlayLayer::onTouchesCancelled(const std::vector<Touch*>& touches, cocos2d::Event  *event)
{
	this->mRunner->getb2PhysicsBody()->getBody()->SetLinearVelocity(b2Vec2(20.0f, 0));

}
#pragma endregion

#pragma region collision and response

void GamePlayLayer::BeginContact(b2Contact* contact)
{
	auto nodeA = (Node*)contact->GetFixtureA()->GetBody()->GetUserData();
	auto nodeB = (Node*)contact->GetFixtureB()->GetBody()->GetUserData();

	if (nodeA && nodeB)
	{
		int aTag = nodeA->getTag();
		int bTag = nodeB->getTag();

		if (aTag == TAG_OBJECT_PLAYER)
		{
			switch (bTag)
			{
			case TAG_OBJECT_GROUND:{
									   this->mRunner->collideGround(nodeB);
									   break;
			}
			default:
				break;
			}
		}
		else
		{
			if (bTag == TAG_OBJECT_PLAYER)
			{
				switch (aTag)
				{
				case TAG_OBJECT_GROUND:{
										   this->mRunner->collideGround(nodeA);
										   break;

				}
				default:
					break;
				}
			}
		}
	}
}


void GamePlayLayer::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{
	//return true;
}

void GamePlayLayer::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
{
}

void GamePlayLayer::EndContact(b2Contact* contact)
{

}

#pragma endregion
