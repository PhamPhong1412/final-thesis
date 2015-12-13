#ifndef __SOUND_MANAGER_H__
#define __SOUND_MANAGER_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

class SoundManager
{
private:
	CocosDenshion::SimpleAudioEngine* audio;
	static SoundManager* instance;
public:
	static SoundManager* inst();
	void init();

	void playBackgroundTheme(bool isLoop = true);

	void playBulletBlock(int index);
	void playBulletShoot(int index);
	//void playArrowEffect(bool isLoop = false);

};

#endif