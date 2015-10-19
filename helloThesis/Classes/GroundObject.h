#ifndef __GROUND_H__
#define __GROUND_H__

#include "cocos2d.h"
#include "b2Node.h"
#include "Utility.h"

enum GroundType{
	NORMAL, SLOPE
};

class GroundObject : public b2Node
{
private:
	Sprite* mBody;
	GroundType type;
	NodeDirection dir;
public:

	GroundObject(float xLoc, float yLoc, std::string tileName);

	
};



#endif