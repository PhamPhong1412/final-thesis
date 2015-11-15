#ifndef __QUADTREE_H__
#define __QUADTREE_H__

#include <iostream>
#include <string>
#include "Utility.h"
#include "GameConfig.h"
#include <map>
#include <set>
using namespace std;

typedef struct QuadRect
{
	float top, bot, left, right;
	QuadRect()
		: top(0)
		, bot(0)
		, left(0)
		, right(0)
	{}
	QuadRect(float aTop, float aBot, float aLeft, float aRight)
		: top(aTop)
		, bot(aBot)
		, left(aLeft)
		, right(aRight)
	{}
};

typedef struct ObjectNode
{
	// x, y index of object in the map array NOT in the world map
	//float x, y, w, h;  
	std::string name; //the name of the object
	QuadRect rect;
	string id;

	ObjectNode(QuadRect r, std::string objectName, string identify)
		:rect(r)
		, name(objectName)
		, id(identify){}
	/*ObjectNode(float xLoc, float yLoc, std::string objectName)
		: x(xLoc)
		, y(yLoc)
		, name(objectName)
		, w(TILE_SIZE)
		, h(TILE_SIZE)
	{}

	ObjectNode(float xLoc, float yLoc, float width, float height, std::string objectName)
		: x(xLoc)
		, y(yLoc)
		, w(width)
		, h(height)
		, name(objectName)
	{}*/
};

class QuadNode 
{
private:
	bool intersect(QuadRect rect, ObjectNode object);
	long nodeID;

	std::vector<ObjectNode> listObject;

	QuadNode* leftTopNode;
	QuadNode* rightTopNode;
	QuadNode* leftBotNode;
	QuadNode* rightBotNode;
public:
	QuadRect nodeRect;

	static bool intersect(QuadRect rect, QuadRect objectRect);
	QuadNode(QuadRect rect, std::vector<ObjectNode> objects, vector<int>* tmp, long ID);
	QuadNode(std::string map, vector<int>* tmp);

	vector<ObjectNode>* getObjectFromQuadtree(QuadRect camera, vector<ObjectNode>* objectsTobeAdd,
		set<string>* currentObject, vector<QuadNode*>* currentQuadNodeID);

	vector<ObjectNode>* removeObjectFromQuadtree(QuadRect camera, vector<ObjectNode>* objectsTobeRemove,
		set<string>* currentObject, vector<QuadNode*>* currentQuadNode);
};



#endif