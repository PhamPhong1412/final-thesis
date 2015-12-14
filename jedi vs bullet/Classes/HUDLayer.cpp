#include "HUDLayer.h"

HUDLayer::HUDLayer(Layer* parent, bool canExit){
	this->init(parent, canExit);
	this->autorelease();
}

HUDLayer::~HUDLayer(){
}

// on "init" you need to initialize your instance
bool HUDLayer::init(Layer* parent, bool canExitTouchOnSite)
{
	if (!Layer::init())
	{
		return false;
	}

	auto bg = cocos2d::LayerColor::create(Color4B(53, 53, 53, 100));
	this->addChild(bg);

	for (auto node : parent->getChildren()){
		if (node->getTag() == TAG_NORMAL_LAYER){
			//Director::getInstance()->getEventDispatcher()->pauseEventListenersForTarget(node);
			node->pause();
		}
	}
	//parent->pause();
	this->parent = parent;

	this->setTag(TAG_HUD_LAYER);
	return true;
}

void HUDLayer::exit(){
	//	parent->resume();
	//	for (CCNode* node : parent->getChildren()){
	//		if (node->getTag() == TAG_NORMAL_LAYER){
	//			node->resume();
	//		}
	//	}
		//parent->removeChild(this);
	//this->release();
}
