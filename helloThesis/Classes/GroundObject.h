#ifndef __GROUND_H__
#define __GROUND_H__

#include "cocos2d.h"
#include "b2Node.h"
#include "Utility.h"

enum GroundType{
	NORMAL, BARNORMAL, BARSLOPE, SLOPE, END, START
};

class GroundObject : public b2Node
{
private:
	Sprite* mBody;
	GroundType type;
	NodeDirection dir;
	bool isChangeDirectionTile;

	void createNormalPhysicBody(Sprite* sprite);
	void createSlopePhysicBody(Sprite* sprite, std::string type);
	void createBarNormalPhysicBody(Sprite* sprite);
	void createBarSlopePhysicBody(Sprite* sprite, std::string type);
	void createEndlPhysicBody(Sprite* sprite);
public:

	GroundObject(float xLoc, float yLoc, std::string tileName);

	static bool isChangeDirTile(Node* tile);
	GroundType getType();
	static std::vector<GroundObject*> changeDirectionTiles;
	
};



#endif