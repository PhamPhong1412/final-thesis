#include "GamePlayLayer.h"

// on "init" you need to initialize your instance
bool tmp = false;
bool GamePlayLayer::init()
{
	if (!b2Layer::init())
	{
		return false;
	}
	
	Size visibleSize = Director::getInstance()->getVisibleSize();

	mRunner = Runner::create();
	mRunner->setb2Position(100, 200);
	//mRunner->setPosition(200, 500);
	this->addChild(mRunner);
	mRunner->getb2PhysicsBody()->getBody()->SetLinearVelocity(b2Vec2(0.0f, 0));
	initTiles();
	//createTiles(100, 100);
	//createTiles(100, 300);
	createSlope(500, true);

	auto onTouchListener = EventListenerTouchAllAtOnce::create();
	onTouchListener->onTouchesBegan = CC_CALLBACK_2(GamePlayLayer::onTouchesBegan, this);
	onTouchListener->onTouchesMoved = CC_CALLBACK_2(GamePlayLayer::onTouchesMoved, this);
	onTouchListener->onTouchesEnded = CC_CALLBACK_2(GamePlayLayer::onTouchesEnded, this);
	onTouchListener->onTouchesCancelled = CC_CALLBACK_2(GamePlayLayer::onTouchesCancelled, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(onTouchListener, this);

	this->scheduleUpdate();

	return true;
}

void GamePlayLayer::update(float delta){

	b2Layer::update(delta);
	if (tmp){
		this->mRunner->getb2PhysicsBody()->getBody()->SetLinearVelocity(b2Vec2(10.0f, 0));
	}
	Director::getInstance()->setp
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
		b2Node* b2Tiles = b2Node::create();
		b2Tiles->addChild(sprite);
		int num = 2;
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

#pragma region touch even
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