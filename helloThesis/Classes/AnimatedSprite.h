	#ifndef __B2_ANIMATED_SPRITE_H__
#define __B2_ANIMATED_SPRITE_H__

#include "cocos2d.h"
#include "GameConfig.h"
#include "b2PhysicsBody.h"
#include "b2Integration.h"

#define TAG_ANIMATED_SPRITE	-1000

USING_NS_CC;

class AnimatedSprite :public Sprite, public b2Integration
{
private:
public:
	//Init sprite with Texture
	bool initWithTexture(Texture2D* texture);

	Vector<SpriteFrame*> Frames;
	Dictionary* settings;

	void initPhysicBody();
	void setFrame(int frame);
	//Initialize
	static AnimatedSprite* create(std::string filepath);
	static AnimatedSprite* create(std::string filepath, int columns, int rows);
	static AnimatedSprite* createWithPhysicsBody(std::string filepath);
	static AnimatedSprite* createWithPhysicsBody(std::string filepath, int columns, int rows);
	
	bool init();
	bool init(std::string filepath, int columns, int rows);
	void initSettingVectorFrames(std::vector<int> &frames, std::string attribute);
	int getSettingIntValue(std::string attribute);

	//animate this sprite with a specific list frames
	void animate(float animationdelay, std::vector<int>frames);
	void animate(float animationdelay, std::vector<int> frames, int loop);
	void animateWithAutoRelease(float animationdelay, std::vector<int> frames, int loop);
	void animateWithAutoRelease(float animationdelay, int loop);

	Animate* createAnimate(float animationdelay, std::vector<int> frames, int loop);

	void setb2PhysicsBody(b2PhysicsBody* body);
	//void replaceb2PhysicsBody(b2PhysicsBody* body);

	//Sprite properties
	CC_SYNTHESIZE(int, _rows, Rows);
	CC_SYNTHESIZE(int, _rolumns, Columns);
	CC_SYNTHESIZE(int, _width, Width);
	CC_SYNTHESIZE(int, _height, Height);
	//Times loop
	CC_SYNTHESIZE(int, _loopTime, LoopTime);

	CREATE_FUNC(AnimatedSprite);
};

#endif
