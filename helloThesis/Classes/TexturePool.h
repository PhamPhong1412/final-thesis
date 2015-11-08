#ifndef _TEXTURE_POOL_H_
#define _TEXTURE_POOL_H_
#include "cocos2d.h"
#include <map>
USING_NS_CC;

class TexturePool
{
private:
	Map<std::string, Texture2D*>* pool;
	static TexturePool* instance;
	void init();
public:
	~TexturePool();
	static TexturePool* getInstance();

};

#endif 
