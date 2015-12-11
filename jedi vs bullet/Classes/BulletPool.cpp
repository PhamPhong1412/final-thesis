#include "BulletPool.h"
#include "GameConfig.h"

bool BulletPool::init(){
	Size visibleSize = Director::getInstance()->getVisibleSize();

	//scale = ((visibleSize.height - 50)/2) / (50 / GameConfig::scale);
	scale = 1;
	this->setTag(55);
	time = 0;
	nextShootTime = 0;

	this->scheduleUpdate();
	shootBullet();
	return true;
}

void BulletPool::update(float delta){
	time += delta;
	if (time > nextShootTime)
		shootBullet();

}

void BulletPool::shootBullet(){
	Size visibleSize = Director::getInstance()->getVisibleSize();
	int shootEdge = RandomHelper::random_int(1, 8);

	int randomPos = 0;
	switch (shootEdge)
	{
	case 1: randomPos = RandomHelper::random_int(0, (int)visibleSize.width / 4); break;
	case 2: randomPos = RandomHelper::random_int(0, (int)visibleSize.height / 4); break;
	case 3: randomPos = RandomHelper::random_int(0, (int)visibleSize.height / 4); break;
	case 4: randomPos = RandomHelper::random_int(0, (int)visibleSize.width / 4); break;
	case 5: randomPos = RandomHelper::random_int(0, (int)visibleSize.width / 4); break;
	case 6: randomPos = RandomHelper::random_int(0, (int)visibleSize.height / 4); break;
	case 7: randomPos = RandomHelper::random_int(0, (int)visibleSize.height / 4); break;
	case 8: randomPos = RandomHelper::random_int(0, (int)visibleSize.width / 4); break;
	}

	//scale = ((visibleSize.height - 50) / 2) / (50 / GameConfig::scale);
	scale = GameConfig::scale;
	randomPos *= scale;

	Vec2 root;
	switch (shootEdge)
	{
	case 1: root = Vec2(DESIGN_SCREEN_WIDTH - randomPos, DESIGN_SCREEN_HEIGHT); break;
	case 2: root = Vec2(DESIGN_SCREEN_WIDTH, DESIGN_SCREEN_HEIGHT - randomPos); break;
	case 3: root = Vec2(DESIGN_SCREEN_WIDTH, 0 + randomPos); break;
	case 4: root = Vec2(DESIGN_SCREEN_WIDTH - randomPos, 0); break;
	case 5: root = Vec2(0 + randomPos, 0); break;
	case 6: root = Vec2(0, 0 + randomPos); break;
	case 7: root = Vec2(0, DESIGN_SCREEN_HEIGHT - randomPos); break;
	case 8: root = Vec2(0 + randomPos, DESIGN_SCREEN_HEIGHT); break;
	}
	
	//root = Vec2(DESIGN_SCREEN_WIDTH, DESIGN_SCREEN_HEIGHT - randomPos); 
	Vec2 velocity = Vec2(-0.5, -0.5);
	Bullet* bullet = Bullet::create();

	int tmpRand = RandomHelper::random_int(0, 5);
	int diff = 25 + tmpRand;
	switch (shootEdge){
	case 1:
	case 2:
	case 7:
	case 8:bullet->targetPoint = Vec2(DESIGN_SCREEN_WIDTH / 2 - 5 *scale, DESIGN_SCREEN_HEIGHT / 2 + diff*scale); break;
	default: bullet->targetPoint = Vec2(DESIGN_SCREEN_WIDTH / 2 - 5 * scale, DESIGN_SCREEN_HEIGHT / 2); break;
	}

	bullet->setPosition(root);
	bullet->velocity = velocity;
	auto moveTo = MoveTo::create(1.5, bullet->targetPoint);
	bullet->runAction(moveTo);

	this->addChild(bullet);
	pool.push_back(bullet);
}
