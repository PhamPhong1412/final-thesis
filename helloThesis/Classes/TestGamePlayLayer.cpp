#include "TestGamePlayLayer.h"
#include "MapMakingScene.h"


// on "init" you need to initialize your instance
bool TestGamePlayLayer::init(std::string map, Layer *parentLayer)
{
	if (!b2Layer::init())
	{
//		return false;
	}
	time = 0;
	mCanUpMap = false;
	Size visibleSize = Director::getInstance()->getVisibleSize();
	this->mMap = map;
    this->mParentLayer = parentLayer;
	mRunner = Runner::create();
	mRunner->mModel->setb2Position(50, 300);
	mRunner->setPosition(50, 300);
	this->addChild(mRunner);
	mRunner->mModel->setVelocityX(15.0f);
	vector<int>* t = new vector<int>();
	t->push_back(0);
	t->push_back(0);
	t->at(0) = 0;
	t->at(1) = 0;

	quadTree = new QuadNode(map, t);
	currentObjectList = new set<string>();
	currentQuadNode = new vector<QuadNode*>();
	quadtreeUpdateCounter = 10;
	updateQuadTree();
	
	auto listener = EventListenerTouchOneByOne::create();

	listener->onTouchBegan = CC_CALLBACK_2(TestGamePlayLayer::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(TestGamePlayLayer::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(TestGamePlayLayer::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	this->scheduleUpdate();

	this->runAction(cocos2d::Follow::create(mRunner, Rect(0 - 53, 0 - 18, quadTree->nodeRect.right ,
		quadTree->nodeRect.top )));

	this->setTag(TAG_NORMAL_LAYER);
	return true;
}

void TestGamePlayLayer::update(float delta){
	time += delta;
    this->mDelegate->testUpdateTime(time);
    
	if (mRunner->mModel->finish() && !mCanUpMap)
	{
        this->mDelegate->testUpdateTime(0);
		mCanUpMap = true;
		//mRunner->mModel->setFinish(false);
		chooseLayer = new GameHUDLayer(this->mParentLayer, time);
		chooseLayer->setDelegate(this);
		//this->removeChild(menu);
		this->addChild(chooseLayer);
	}
	else
	{
		updateQuadTree();
		b2Layer::update(delta);
	}
	
}

void TestGamePlayLayer::uploadMap()
{
	CCLOG("result");
	auto mapMakingScene = MapMakingScene::createScene();
	Director::getInstance()->replaceScene(mapMakingScene);
}

void TestGamePlayLayer::exitBack()
{
	auto mapMakingScene = MapMakingScene::createScene();
	Director::getInstance()->replaceScene(mapMakingScene);
}

void TestGamePlayLayer::saveMap()
{
	cocos2d::log("%s", this->mMap.c_str());

	std::vector<HttpRequestParameter> resData{ HttpRequestParameter(phoneKey, "test"), HttpRequestParameter(mapData, this->mMap) };
	HttpServices::inst->sendRequest(chooseLayer, resData, HttpRequestMethod::UPLOAD_MAP);
	HttpServices::inst->setDelegate(this);
}

void TestGamePlayLayer::addTile(std::string tileName, float xLoc, float yLoc){
    if (tileName == "0")
        return;

	GroundObject* go = new GroundObject(xLoc, yLoc, tileName);
	this->addChild(go);
}

#pragma region touch event
bool TestGamePlayLayer::onTouchBegan(Touch *touch, Event *event){
	this->mRunner->jump();
	return true;
}

void TestGamePlayLayer::onTouchMoved(Touch *touch, Event *event)
{

}

void TestGamePlayLayer::onTouchEnded(Touch *touch, Event *event)
{

}

void TestGamePlayLayer::onTouchCancelled(Touch *touch, Event *event)
{
	//this->mRunner->getb2PhysicsBody()->getBody()->SetLinearVelocity(b2Vec2(20.0f, 0));

}
#pragma endregion

#pragma region collision and response

void TestGamePlayLayer::BeginContact(b2Contact* contact)
{
	auto nodeA = (b2Node*)contact->GetFixtureA()->GetBody()->GetUserData();
	auto nodeB = (b2Node*)contact->GetFixtureB()->GetBody()->GetUserData();

	if (nodeA && nodeB)
	{
		int aTag = nodeA->getTag();
		int bTag = nodeB->getTag();

		if (aTag == TAG_OBJECT_PLAYER)
		{
			if (bTag == TAG_OBJECT_SLOW){
				GroundObject* snow = (GroundObject*)contact->GetFixtureB()->GetBody()->GetUserData();
				mRunner->collideSnowTile(snow);
			}

			if (bTag == TAG_OBJECT_BOMB){
				GroundObject* bomb = (GroundObject*)contact->GetFixtureB()->GetBody()->GetUserData();
				mRunner->collideBombTile(bomb);
			}

			else{
				this->mRunner->BeginContact(nodeB, contact);
			}
		}
		else
		{
			if (bTag == TAG_OBJECT_PLAYER)
			{
				if (aTag == TAG_OBJECT_SLOW){
					GroundObject* snow = (GroundObject*)contact->GetFixtureA()->GetBody()->GetUserData();
					mRunner->collideSnowTile(snow);
				}

				if (aTag == TAG_OBJECT_BOMB){
					GroundObject* bomb = (GroundObject*)contact->GetFixtureA()->GetBody()->GetUserData();
					mRunner->collideBombTile(bomb);
				}

				this->mRunner->BeginContact(nodeA, contact);
			}
		}
	}
}

void TestGamePlayLayer::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{
	this->BeginContact(contact);
	//return true;
}

void TestGamePlayLayer::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
{
	this->BeginContact(contact);
}

void TestGamePlayLayer::EndContact(b2Contact* contact)
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

void TestGamePlayLayer::updateQuadTree(){

	if (quadtreeUpdateCounter++ > 10){
		quadtreeUpdateCounter = 0;

		QuadRect cameraRect = QuadRect(DESIGN_SCREEN_HEIGHT + this->mRunner->getPosition().y, this->mRunner->getPosition().y - DESIGN_SCREEN_HEIGHT,
			this->mRunner->getPosition().x - DESIGN_SCREEN_WIDTH,
			this->mRunner->getPosition().x + DESIGN_SCREEN_WIDTH);
		std::vector<ObjectNode>* object2bAdd = new std::vector<ObjectNode>();
		std::vector<ObjectNode>* object2bRemove = new std::vector<ObjectNode>();
		
		object2bAdd = this->quadTree->getObjectFromQuadtree(cameraRect,
			object2bAdd, this->currentObjectList, this->currentQuadNode);

		for (int i = 0; i != object2bAdd->size(); i++) {
			//addTile(origin->at(i).name, origin->at(i).rect.left + TILE_SIZE / 2, origin->at(i).rect.bot + TILE_SIZE / 2);
			//if (this->getChildByName(origin->at(i).id) != nullptr)
			//	continue;
			GroundObject* go = new GroundObject(object2bAdd->at(i).rect.left + TILE_SIZE / 2,
				object2bAdd->at(i).rect.bot + TILE_SIZE / 2, object2bAdd->at(i).name);
			go->setName(object2bAdd->at(i).id);
			this->addChild(go);
		}

		object2bRemove = this->quadTree->removeObjectFromQuadtree(cameraRect,
			object2bRemove, this->currentObjectList, this->currentQuadNode);

		for (int i = 0; i != object2bRemove->size(); i++) {
			this->removeChildByName(object2bRemove->at(i).id);
		}
	}
}