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
	mRunner->mModel->setb2Position(1900, 300);
	mRunner->setPosition(1900, 300);
	this->addChild(mRunner);
	vector<int>* t = new vector<int>();
	t->push_back(0);
	t->push_back(0);
	t->at(0) = 0;
	t->at(1) = 0;

	quadTree = new QuadNode(map, t);
	currentObjectList = new set<string>();
	currentQuadNode = new vector<QuadNode*>();
	updateQuadTree();

	/*std::vector<std::string> part = Utility::splitString(map, "dm");

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
*/
	auto listener = EventListenerTouchOneByOne::create();

	listener->onTouchBegan = CC_CALLBACK_2(GamePlayLayer::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(GamePlayLayer::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(GamePlayLayer::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	this->scheduleUpdate();

	//this->runAction(cocos2d::Follow::create(mRunner, Rect(0, 0, x / GameConfig::scale,
	//	y / GameConfig::scale)));
	this->runAction(cocos2d::Follow::create(mRunner, Rect(0, 0, quadTree->nodeRect.right / GameConfig::scale,
		quadTree->nodeRect.top / GameConfig::scale)));

	this->setTag(TAG_NORMAL_LAYER);
	return true;
}

void GamePlayLayer::update(float delta){
	if (quadtreeUpdateCounter++ > 1){
		quadtreeUpdateCounter=0;
		updateQuadTree();
	}
	b2Layer::update(delta);
}

void GamePlayLayer::addTile(std::string tileName, float xLoc, float yLoc){
    if (tileName == "0")
        return;

	GroundObject* go = new GroundObject(xLoc, yLoc, tileName);
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

void GamePlayLayer::updateQuadTree(){
	std::vector<ObjectNode>* object2bRemove = new std::vector<ObjectNode>();
	std::vector<ObjectNode>* object2bAdd = new std::vector<ObjectNode>();

	QuadRect cameraRect = QuadRect(DESIGN_SCREEN_HEIGHT,0,
		this->mRunner->getPosition().x - DESIGN_SCREEN_WIDTH / 2,
		this->mRunner->getPosition().x + DESIGN_SCREEN_WIDTH / 2);

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

	//for (int i = 0; i != currentObjectList->size(); i++) {
	//	//addTile(origin->at(i).name, origin->at(i).rect.left + TILE_SIZE / 2, origin->at(i).rect.bot + TILE_SIZE / 2);
	//	//Node* object = this->getChildByName(currentObjectList);
	//	//if (QuadNode::intersect(cameraRect, )
	//	//	continue;
	//}
}