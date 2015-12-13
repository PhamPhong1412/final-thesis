#include "SoundManager.h"
USING_NS_CC;
SoundManager* SoundManager::instance = NULL;

SoundManager* SoundManager::inst(){
	if (!instance){
		instance = new SoundManager();
		instance->init();
	}
	return instance;
}

void SoundManager::init(){
	this->audio = CocosDenshion::SimpleAudioEngine::getInstance();

	this->audio->preloadEffect("1.wav");
	this->audio->preloadEffect("2.wav");
	this->audio->preloadEffect("3.wav");

	this->audio->preloadEffect("Laser Shot 4.wav");
	this->audio->preloadEffect("Laser Shot 5.wav");
	this->audio->preloadEffect("Laser Shot 6.wav");
}


void SoundManager::playBulletBlock(int index){
	switch (index){
	case 1: this->audio->playEffect("1.wav"); break;
	case 2: this->audio->playEffect("2.wav"); break;
	case 3: this->audio->playEffect("3.wav"); break;
	}
}

void SoundManager::playBulletShoot(int index){
	switch (index){
	case 4: this->audio->playEffect("Laser Shot 4.wav"); break;
	case 5: this->audio->playEffect("Laser Shot 6.wav"); break;
	case 6: this->audio->playEffect("Laser Shot 6.wav"); break;
	}
}