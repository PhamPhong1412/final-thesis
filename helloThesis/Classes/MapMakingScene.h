#ifndef _MAP_MAKING_SCENE_H_
#define _MAP_MAKING_SCENE_H_


#include "cocos2d.h"
#include "extensions\GUI\CCScrollView\CCScrollView.h"
//#include "ui\CocosGUI.h"
using namespace cocos2d;
using namespace cocos2d::extension;

class MapMakingScene : public Layer
{
private:
    
public:
    
    static cocos2d::Scene* createScene();
	cocos2d::extension::ScrollView *scrollView;
    Layer *scrollContainer;
    
    virtual bool init();
    
    CREATE_FUNC(MapMakingScene);
};

#endif