#include "QuadNode.h"

QuadNode::QuadNode(QuadRect rect, std::vector<ObjectNode> objects, vector<int>* tmp, long ID){

	tmp->at(0) = tmp->at(0) + 1;
	this->nodeRect = rect;
	float midX = (rect.left + rect.right) / 2;
	float midY = (rect.top + rect.bot) / 2;
	float width = (-rect.left + rect.right);
	float height = (rect.top - rect.bot);
	for (auto &object : objects){
		if (intersect(rect, object)){
			listObject.push_back(object);
		}
	}
	this->nodeID = ID;
	if (listObject.size() == 0 || height*2 <= DESIGN_SCREEN_HEIGHT || width <= DESIGN_SCREEN_WIDTH){
		leftTopNode = leftBotNode = rightTopNode = rightBotNode = nullptr;
		tmp->at(1) = tmp->at(1) + listObject.size();
		return;
	}

	//if (listObject.size() == 0){
	//	leftTopNode = leftBotNode = rightTopNode = rightBotNode = nullptr;
	//	tmp->at(1) = tmp->at(1) + listObject.size();
	//	return;
	//}

	//if ( height*2 > DESIGN_SCREEN_HEIGHT && width > DESIGN_SCREEN_WIDTH){
	//	this->leftTopNode = new QuadNode(QuadRect(rect.top, midY, rect.left, midX), listObject, tmp, ID * 4 + 1);

	//	this->leftBotNode = new QuadNode(QuadRect(midY, rect.bot, rect.left, midX), listObject, tmp, ID * 4 + 2);

	//	this->rightTopNode = new QuadNode(QuadRect(rect.top, midY, midX, rect.right), listObject, tmp, ID * 4 + 3);

	//	this->rightBotNode = new QuadNode(QuadRect(midY, rect.bot, midX, rect.right), listObject, tmp, ID * 4 + 4);
	//	listObject.clear();
	//	return;
	//}

	//if (height*2 > DESIGN_SCREEN_HEIGHT){
	//	this->leftTopNode = new QuadNode(QuadRect(rect.top, midY, rect.left, midX), listObject, tmp, ID * 4 + 1);

	//	this->leftBotNode = new QuadNode(QuadRect(midY, rect.bot, rect.left, midX), listObject, tmp, ID * 4 + 2);

	//	this->rightTopNode = new QuadNode(QuadRect(rect.top, midY, midX, rect.right), listObject, tmp, ID * 4 + 3);

	//	this->rightBotNode = new QuadNode(QuadRect(midY, rect.bot, midX, rect.right), listObject, tmp, ID * 4 + 4);
	//	listObject.clear();
	//	return;
	//}

	//if ( width <= DESIGN_SCREEN_WIDTH){
	//	this->leftTopNode = new QuadNode(QuadRect(rect.top, midY, rect.left, rect.right), objects, tmp);

	//	this->leftBotNode = new QuadNode(QuadRect(midY, rect.bot, rect.left, rect.right), objects, tmp);
	//	 rightTopNode = rightBotNode = nullptr;
	//	return;
	//}

	//if (height <= DESIGN_SCREEN_HEIGHT ){
	//	this->rightTopNode = new QuadNode(QuadRect(rect.top, rect.bot, midX, rect.right), objects, tmp);

	//	this->rightBotNode = new QuadNode(QuadRect(rect.top, rect.bot, rect.left, midX), objects, tmp);
	//	leftTopNode = leftBotNode = nullptr;
	//	return;
	//}
	//
	this->leftTopNode = new QuadNode(QuadRect(rect.top, midY, rect.left, midX), listObject, tmp, ID*4+1);

	this->leftBotNode = new QuadNode(QuadRect(midY, rect.bot, rect.left, midX), listObject, tmp, ID * 4 + 2);

	this->rightTopNode = new QuadNode(QuadRect(rect.top, midY, midX, rect.right), listObject, tmp, ID * 4 + 3);

	this->rightBotNode = new QuadNode(QuadRect(midY, rect.bot, midX, rect.right), listObject, tmp, ID * 4 + 4);
	listObject.clear();
}


QuadNode::QuadNode(std::string map, vector<int>* tmp){
	std::vector<ObjectNode> objects;
	tmp->at(0) = tmp->at(0) + 1;
	std::vector<std::string> part = Utility::splitString(map, "dm");

	std::vector<std::string> widthHeight = Utility::splitString(part.at(0), "\n");
	int nTilesWidth = std::stoi(widthHeight.at(0));
	int nTilesHeight = std::stoi(widthHeight.at(1));


	QuadRect rect(nTilesHeight*TILE_SIZE, 0, 0, nTilesWidth*TILE_SIZE);
	this->nodeRect = rect;
	float midX = (rect.left + rect.right) / 2;
	float midY = (rect.top + rect.bot) / 2;


	float x, y;
	float tileSize = 70 / GameConfig::scale;
	std::vector<std::string> objectData = Utility::splitString(part.at(1), "\n");
	for (int i = 0; i < nTilesHeight; i++){
		y = (int)(nTilesHeight - i - 1) * tileSize;
		int tmp = y;
		y = tmp;
		std::vector<std::string> currentLineData = Utility::splitString(objectData.at(i), ";");
		for (int j = 0; j < nTilesWidth; j++){
			std::string tileName = currentLineData.at(j);
			if (tileName == "0")
				continue;
			x = j * tileSize;
			string tmp = std::to_string(x) +  "," + std::to_string(y);
 			objects.push_back(ObjectNode(QuadRect(y + tileSize / 2, y - tileSize / 2, x - tileSize / 2, x + tileSize / 2), tileName, tmp));
		}
	}
	

	this->leftTopNode = new QuadNode(QuadRect(rect.top, midY, rect.left, midX), objects, tmp, 0);

	this->leftBotNode = new QuadNode(QuadRect(midY, rect.bot, rect.left, midX), objects, tmp, 1);

	this->rightTopNode = new QuadNode(QuadRect(rect.top, midY, midX, rect.right), objects, tmp, 2);

	this->rightBotNode = new QuadNode(QuadRect(midY, rect.bot, midX, rect.right), objects, tmp, 3);
	objects.clear();
	this->listObject = objects;
}


bool QuadNode::intersect(QuadRect rect, ObjectNode object){
	bool topCheck = rect.top < object.rect.bot;
	bool botCheck = rect.bot > object.rect.top;
	bool leftCheck = rect.left > object.rect.right;
	bool rightCheck = rect.right < object.rect.left;

	return !(topCheck || botCheck || leftCheck || rightCheck);
}

bool QuadNode::intersect(QuadRect rect, QuadRect object){
	bool topCheck = rect.top < object.bot;
	bool botCheck = rect.bot > object.top;
	bool leftCheck = rect.left > object.right;
	bool rightCheck = rect.right < object.left;

	return !(topCheck || botCheck || leftCheck || rightCheck);
}


vector<ObjectNode>* QuadNode::getObjectFromQuadtree(QuadRect camera,
	vector<ObjectNode>* objectsTobeAdd,
	set<string>* currentObject,  // current object in currentQuadNodeID
	vector<QuadNode*>* currentQuadNode)// current quadnode that intersect with the camera
{
	bool intersectCheck = !intersect(camera, this->nodeRect);
	bool nodeIDCheck = std::find(currentQuadNode->begin(), currentQuadNode->end(), this) != currentQuadNode->end();
	if (intersectCheck || nodeIDCheck)
		return objectsTobeAdd;

	if (this->listObject.size() != 0){
		for (auto &object : this->listObject){
			if (currentObject->find(object.id) == currentObject->end()){
				currentObject->insert(object.id);
				objectsTobeAdd->push_back(object);
			}
		}
		currentQuadNode->push_back(this);
	}
	else{
		if (this->leftBotNode != nullptr)
			leftBotNode->getObjectFromQuadtree(camera, objectsTobeAdd, currentObject, currentQuadNode);

		if (this->leftTopNode != nullptr)
			leftTopNode->getObjectFromQuadtree(camera, objectsTobeAdd, currentObject, currentQuadNode);

		if (this->rightBotNode != nullptr)
			rightBotNode->getObjectFromQuadtree(camera, objectsTobeAdd, currentObject, currentQuadNode);

		if (this->rightTopNode != nullptr)
			rightTopNode->getObjectFromQuadtree(camera, objectsTobeAdd, currentObject, currentQuadNode);
	}

	return objectsTobeAdd;
}


vector<ObjectNode>* QuadNode::removeObjectFromQuadtree(QuadRect camera,
	vector<ObjectNode>* objectsTobeRemove,
	set<string>* currentObject,  // current object in currentQuadNodeID
	vector<QuadNode*>* currentQuadNode)// current quadnode that intersect with the camera
{
	vector< QuadNode* >::iterator it = currentQuadNode->begin();

	for (int i = 0; i < currentQuadNode->size(); i++){
		if (!QuadNode::intersect(camera, currentQuadNode->at(i)->nodeRect)){

			for (auto &object : currentQuadNode->at(i)->listObject){
				objectsTobeRemove->push_back(object);
				currentObject->erase(currentObject->find(object.id));
			}

			currentQuadNode->erase(currentQuadNode->begin() + i);
		}
	}
	return objectsTobeRemove;
}