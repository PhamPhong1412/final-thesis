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
	//shootBullet();
	initShootTime();
	lastEdge = 1;
	return true;
}

void BulletPool::update(float delta){
	time += delta;
	for (int i = 0; i < shootTime.size(); i++){
		if (time > shootTime[i]){
			shootBullet();
			shootTime.erase(shootTime.begin() + i);
		}
	}
	if (shootTime.size() == 0){
		generateShootPattern();
	}

}

void BulletPool::shootBullet(){
	Size visibleSize = Director::getInstance()->getVisibleSize();
	int shootEdge = RandomHelper::random_int(1, 8);
	while (shootEdge == lastEdge){
		shootEdge = RandomHelper::random_int(1, 8);
	}
	lastEdge = shootEdge;

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
	case 8: randomPos = RandomHelper::random_int(0, (int)visibleSize.width / 3); break;
	}

	scale = GameConfig::scale;
	//randomPos *= scale;

	Vec2 root;
	switch (shootEdge)
	{
	case 1: root = Vec2(DESIGN_SCREEN_WIDTH - randomPos, DESIGN_SCREEN_HEIGHT); break;
	case 2: root = Vec2(DESIGN_SCREEN_WIDTH, DESIGN_SCREEN_HEIGHT - randomPos); break;
	case 3: root = Vec2(DESIGN_SCREEN_WIDTH, 0 + randomPos/2); break;
	case 4: root = Vec2(DESIGN_SCREEN_WIDTH - randomPos, 0); break;
	case 5: root = Vec2(0 + randomPos, 0); break;
	case 6: root = Vec2(0, 0 + randomPos/2); break;
	case 7: root = Vec2(0, DESIGN_SCREEN_HEIGHT - randomPos); break;
	case 8: root = Vec2(0 + randomPos, DESIGN_SCREEN_HEIGHT); break;
	}
	
	Bullet* bullet = Bullet::create();
	
	float rotate=0;
	switch (shootEdge)
	{
	case 1: rotate = 0 - 90.0f*(root.x - visibleSize.width / 2) / (visibleSize.width); break;
	case 2: rotate = 0 - 90.0f*(root.y - visibleSize.height / 2) / (visibleSize.height); break;
	case 3: rotate = 0 - 90.0f*(root.y - visibleSize.height / 2) / (visibleSize.height); break;
	case 4: rotate = 0 + 90.0f*(root.x - visibleSize.width / 2) / (visibleSize.width); break;
	case 5: rotate = 0 + 90.0f*(root.x - visibleSize.width / 2) / (visibleSize.width); break;
	case 6: rotate = 0 + 90.0f*(root.y - visibleSize.height / 2) / (visibleSize.height); break;
	case 7: rotate = 45 - 45.0f*(root.y - visibleSize.height / 2) / (visibleSize.height); break;
	case 8: rotate = 45 + 45.0f*(root.x - visibleSize.width / 2) / (visibleSize.width); break;
	}


	auto rotateBy = RotateBy::create(0, rotate);
	bullet->runAction(rotateBy);

	//bullet->setRotationY(rotate);
	bullet->setPosition(root);
	
	
	int tmp = RandomHelper::random_int(10, 40);
	switch (shootEdge){
	case 2:
	case 7:
	case 8:
	case 1: bullet->targetPoint = Vec2(DESIGN_SCREEN_WIDTH / 2, DESIGN_SCREEN_HEIGHT / 2 - 40 + 10 + tmp); break;
	default: bullet->targetPoint = Vec2(DESIGN_SCREEN_WIDTH / 2, DESIGN_SCREEN_HEIGHT / 2 - 40 - 15 - tmp); break;
	}

	int direction;

	if (bullet->getPosition().x > bullet->targetPoint.x)
		bullet->direction = 1;
	else
		bullet->direction = -1;

	bullet->attackEdge = shootEdge;

	auto moveTo = MoveTo::create(0.75, bullet->targetPoint);
	bullet->runAction(moveTo);
	this->addChild(bullet);
	pool.push_back(bullet);
	int i = RandomHelper::random_int(4, 6);
	SoundManager::inst()->playBulletShoot(i);
}

void BulletPool::generateShootPattern(){
	int randValue = RandomHelper::random_int(1, 100);
	float speed = 1 - GameConfig::currentScore / 400;
	if (speed < 0.5f)
		speed = 0.5f;

	if (randValue % 4 == 0){
		for (float i = 0; i < RandomHelper::random_int(3,10); i += 1.0f){
			float x = RandomHelper::random_real(0.3f, 1.1f);
			if (i == 0){
				shootTime.push_back(0.75f / speed + time + RandomHelper::random_real(0.3f, 1.1f)*speed);
			}
			else{
				shootTime.push_back(shootTime[i - 1] + RandomHelper::random_real(0.3f, 1.1f)*speed);
			}
		}
	}
	else{
		int tmp = RandomHelper::random_int(1, 9);
		switch (tmp){
		case 1: shootTime = templateSound; break;
		case 2: shootTime = templateSound1; break;
		case 3: shootTime = templateSound2; break;
		case 4: shootTime = templateSound3; break;
		case 5: shootTime = templateSound4; break;
		case 6: shootTime = templateSound5; break;
		case 7: shootTime = templateSound6; break;
		case 8: shootTime = templateSound7; break;
		case 9: shootTime = templateSound8; break;
		}
		//shootTime = templateSound2;

		//speed = 1;
		for (int i = 0; i < shootTime.size(); i++){
			shootTime[i] = shootTime[i] * speed * 1.1 + time + 0.75/speed;
		}
	}


	
}

void BulletPool::initShootTime(){
	templateSound.push_back(0.3f);
	templateSound.push_back(0.6f);
	templateSound.push_back(0.9f);
	templateSound.push_back(1.7f);
	templateSound.push_back(2.0f);
	templateSound.push_back(2.3f);
	templateSound.push_back(3.1f);
	templateSound.push_back(3.4f);
	templateSound.push_back(3.7f);

	templateSound1.push_back(0.75f);
	templateSound1.push_back(1.5f);
	templateSound1.push_back(2.25f);
	templateSound1.push_back(3.0f);
	templateSound1.push_back(3.4f);
	templateSound1.push_back(3.8f);

	templateSound2.push_back(0.3f);
	templateSound2.push_back(0.9f);
	templateSound2.push_back(1.5f);
	templateSound2.push_back(2.1f);
	templateSound2.push_back(2.35f);
	templateSound2.push_back(2.55f);

	templateSound3.push_back(1.1f);
	templateSound3.push_back(2.1f);
	templateSound3.push_back(2.6f);
	templateSound3.push_back(2.85f);
	templateSound3.push_back(3.1f);
	templateSound3.push_back(3.8f);
	templateSound3.push_back(4.8f);
	templateSound3.push_back(5.2f);
	templateSound3.push_back(5.6f);
	templateSound3.push_back(6.0f);
	templateSound3.push_back(6.4f);

	templateSound4.push_back(0.5f);
	templateSound4.push_back(1.0f);
	templateSound4.push_back(1.5f);
	templateSound4.push_back(2.0f);
	templateSound4.push_back(2.5f);
	templateSound4.push_back(3.0f);
	templateSound4.push_back(3.5f);
	templateSound4.push_back(4.0f);
	templateSound4.push_back(4.5f);
	templateSound4.push_back(5.0f);
	templateSound4.push_back(5.5f);
	templateSound4.push_back(6.0f);
	templateSound4.push_back(6.5f);
	templateSound4.push_back(7.0f);
	templateSound4.push_back(7.5f);
	templateSound4.push_back(8.0f);
	templateSound4.push_back(8.5f);
	templateSound4.push_back(9.0f);
	templateSound4.push_back(9.5f);
	templateSound4.push_back(10.0f);
	templateSound4.push_back(10.5f);

	templateSound5.push_back(0.1f);
	templateSound5.push_back(0.25f);
	templateSound5.push_back(0.65f);
	templateSound5.push_back(1.1f);
	templateSound5.push_back(3.1f);
	templateSound5.push_back(3.25f);
	templateSound5.push_back(3.65f);
	templateSound5.push_back(4.1f);
	templateSound5.push_back(6.1f);
	templateSound5.push_back(6.25f);
	templateSound5.push_back(6.65f);
	templateSound5.push_back(7.1f);
	templateSound5.push_back(8.25f);
	templateSound5.push_back(8.45f);
	templateSound5.push_back(8.6f);
	templateSound5.push_back(8.85f);
	templateSound5.push_back(9.05f);

	templateSound6.push_back(0.0f);
	templateSound6.push_back(0.5f);
	templateSound6.push_back(0.8f);
	templateSound6.push_back(1.1f);
	templateSound6.push_back(1.5f);
	templateSound6.push_back(1.8f);
	templateSound6.push_back(2.1f);
	templateSound6.push_back(2.45f);
	templateSound6.push_back(2.75f);
	templateSound6.push_back(3.1f);
	templateSound6.push_back(3.5f);

	templateSound7.push_back(0.4f);
	templateSound7.push_back(0.8f);
	templateSound7.push_back(1.4f);
	templateSound7.push_back(1.8f);
	templateSound7.push_back(2.4f);
	templateSound7.push_back(2.8f);
	templateSound7.push_back(3.4f);
	templateSound7.push_back(3.8f);

	templateSound8.push_back(0.6f);
	templateSound8.push_back(0.9f);
	templateSound8.push_back(1.4f);
	templateSound8.push_back(1.63f);
	templateSound8.push_back(1.91f);
	templateSound8.push_back(2.54f);
	templateSound8.push_back(2.74f);
	templateSound8.push_back(3.15f);
	templateSound8.push_back(3.41f);
	templateSound8.push_back(3.66f);
	templateSound8.push_back(4.16f);
	templateSound8.push_back(4.42f);
	templateSound8.push_back(4.7f);
	templateSound8.push_back(5.08f);
	templateSound8.push_back(5.26f);
	templateSound8.push_back(5.58f);
	templateSound8.push_back(5.99f);
	templateSound8.push_back(6.25f);
	templateSound8.push_back(6.43f);
	templateSound8.push_back(6.7f);
	templateSound8.push_back(6.89f);
	templateSound8.push_back(7.15f);
	templateSound8.push_back(7.37f);


}