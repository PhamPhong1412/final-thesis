#ifndef _MAP_MAKING_SCENE_H_
#define _MAP_MAKING_SCENE_H_


#include "cocos2d.h"
#include "cocos-ext.h"

using namespace cocos2d;
using namespace extension;

USING_NS_CC;

class MapMakingScene : public Layer
{
private:
    
public:
    
    static cocos2d::Scene* createScene();
    ScrollView *scrollView;
    Layer *scrollContainer;
    
    virtual bool init();
    
    CREATE_FUNC(MapMakingScene);
};

#endif