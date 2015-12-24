//
//  TimeHUDLayer.h
//  Run
//
//  Created by TFLAT iOS Developer on 12/24/15.
//
//

#ifndef LoadingHUDLayer_h
#define LoadingHUDLayer_h

#include <stdio.h>
#include "HUDLayer.h"
#include "ui/CocosGUI.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include <cocostudio/ActionTimeline/CSLoader.h>
#include <cocostudio/ActionTimeline/CCActionTimeline.h>
#include <cocostudio/ActionTimeline/CCActionTimelineCache.h>
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#include "cocostudio\ActionTimeline\CSLoader.h"
#include "cocostudio\ActionTimeline\CCActionTimeline.h"
#include "cocostudio\ActionTimeline\CCActionTimelineCache.h"
#endif

USING_NS_CC;

class LoadingHUDLayer : public HUDLayer
{
private:
 
    bool init();
public:
	void exitLoading();
	LoadingHUDLayer(Layer* parent);
	~LoadingHUDLayer();
};


#endif /* TimeHUDLayer_h */
