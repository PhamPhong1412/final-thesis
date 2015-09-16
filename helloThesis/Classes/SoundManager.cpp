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

}
