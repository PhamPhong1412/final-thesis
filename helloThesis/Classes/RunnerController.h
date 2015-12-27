#ifndef __RUNNER_H__
#define __RUNNER_H__

#include "cocos2d.h"

#include "GroundObject.h"
#include "RunnerModel.h"
#include "RunnerView.h"

class Runner : public b2Node
{
private:


	float lastX;
	void collideGround(b2Node* groundNode, b2Contact* contact);
	void endCollideGround();

	void runNormal();

	void update(float delta);

public:
	virtual bool init();
	RunnerView* mView;
	RunnerModel* mModel;
	
	void jump();

	//Physics event
	void BeginContact(b2Node* node, b2Contact* contact);
	void EndContact(b2Node* node, b2Contact* contact);

	CREATE_FUNC(Runner);
};

#endif