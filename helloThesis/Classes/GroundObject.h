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
	bool isChangeDirectionTile;
public:

	GroundObject(float xLoc, float yLoc, std::string tileName, bool changeDirect = false);

	static bool isChangeDirTile(Node* tile);
	static std::vector<GroundObject*> changeDirectionTiles;
	static std::string s;

	
};



#endif