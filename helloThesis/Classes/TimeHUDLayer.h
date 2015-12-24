//
//  TimeHUDLayer.h
//  Run
//
//  Created by TFLAT iOS Developer on 12/24/15.
//
//

#ifndef TimeHUDLayer_h
#define TimeHUDLayer_h

#include <stdio.h>
#include "HUDLayer.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

class TimeHUDLayer : public HUDLayer
{
private:
    Label *timeLabel;
    
    void menuBackCallback();
    bool init();
public:
    void setTimeLabel(float time);
    TimeHUDLayer(Layer* parent);
    ~TimeHUDLayer();

};


#endif /* TimeHUDLayer_h */
