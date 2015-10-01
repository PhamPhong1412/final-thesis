#include "GameBackgroundLayer.h"



// on "init" you need to initialize your instance
bool GameBackgroundLayer::init(std::string backgroundName, std::vector<std::string*>* backgroundObjects)
{
	if (!Layer::init())
	{
		return false;
	}
	
	Sprite* background = Sprite::create(backgroundName + ".png");

	float scaleX = (float)DESIGN_SCREEN_WIDTH / background->getContentSize().width;
	float scaleY = (float)DESIGN_SCREEN_HEIGHT / background->getContentSize().height;
	background->setScaleX(scaleX);
	background->setScaleY(scaleY);
	background->setPosition(Vec2(DESIGN_SCREEN_WIDTH / 2, DESIGN_SCREEN_HEIGHT / 2));
	this->addChild(background);

	for (int i = 0; i < backgroundObjects->size(); i++){
		for (int j = 0; j < backgroundObjects->at(i)->size(); j++){
			if (backgroundObjects->at(i)[j] != ""){
				Sprite* object = Sprite::create(backgroundObjects->at(i)[j] + ".png");
				object->setPosition(Vec2(j*TILE_SIZE + TILE_SIZE / 2, i*TILE_SIZE + TILE_SIZE / 2));
				this->addChild(object);
			}

		}
	}

	this->scheduleUpdate();

	return true;
}

void GameBackgroundLayer::update(float delta){



}
