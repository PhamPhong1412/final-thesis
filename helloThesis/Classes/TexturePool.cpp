#include "TexturePool.h"
TexturePool* TexturePool::instance = NULL;

TexturePool* TexturePool::getInstance(){
	if (!instance){
		instance = new TexturePool();
		instance->init();
	}
	return instance;
}

void TexturePool::init(){
	//Texture2D* tmp = new Texture2D();
	//tmp->initWithImage(new Image());
	//
	//pool->insert("1,2", new Texture2D())
}

TexturePool::~TexturePool(){

}