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

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	this->audio->preloadEffect("1.ogg");
	this->audio->preloadEffect("2.ogg");
	this->audio->preloadEffect("3.ogg");

	this->audio->preloadEffect("Laser Shot 4.ogg");
	this->audio->preloadEffect("Laser Shot 5.ogg");
	this->audio->preloadEffect("Laser Shot 6.ogg");
#else
	this->audio->preloadEffect("1.wav");
	this->audio->preloadEffect("2.wav");
	this->audio->preloadEffect("3.wav");

	this->audio->preloadEffect("Laser Shot 4.wav");
	this->audio->preloadEffect("Laser Shot 5.wav");
	this->audio->preloadEffect("Laser Shot 6.wav");
#endif
}


void SoundManager::playBulletBlock(int index){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	switch (index){
	case 1: this->audio->playEffect("1.ogg"); break;
	case 2: this->audio->playEffect("2.ogg"); break;
	case 3: this->audio->playEffect("3.ogg"); break;
	}
#else
	switch (index){
	case 1: this->audio->playEffect("1.wav"); break;
	case 2: this->audio->playEffect("2.wav"); break;
	case 3: this->audio->playEffect("3.wav"); break;
	}
#endif

}

void SoundManager::playBulletShoot(int index){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	switch (index){
	case 4: this->audio->playEffect("Laser Shot 4.ogg"); break;
	case 5: this->audio->playEffect("Laser Shot 6.ogg"); break;
	case 6: this->audio->playEffect("Laser Shot 6.ogg"); break;
	}
#else
	switch (index){
	case 4: this->audio->playEffect("Laser Shot 4.wav"); break;
	case 5: this->audio->playEffect("Laser Shot 6.wav"); break;
	case 6: this->audio->playEffect("Laser Shot 6.wav"); break;
	}
#endif

}