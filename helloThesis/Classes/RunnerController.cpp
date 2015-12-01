#include "RunnerController.h"
bool isChangeDirection;
bool Runner::init(){
	//this->mModel = RunnerModel::create(); 
	isChangeDirection = false;
	this->mModel = new RunnerModel();
	this->mModel->init();
	this->addChild(mModel);
	this->mModel->getb2PhysicsBody()->setb2Position(100, 100);
	this->setb2PhysicsBody(this->mModel->getb2PhysicsBody());
	this->mView = RunnerView::create();
	this->addChild(mView);
	this->setTag(TAG_OBJECT_PLAYER);
	return true;
}

void Runner::BeginContact(b2Node* node, b2Contact* contact){
//	int targetTag = node->getTag();
//	switch (targetTag)
//	{
//	case TAG_OBJECT_GROUND:{
//							   this->collideGround(node, contact);
//							   break;
//	}
//	default:
//		break;
//	}
    this->collideGround(node, contact);
}

void Runner::collideGround(b2Node* groundNode, b2Contact* contact){
	int groundTag = groundNode->getTag();
	float tmp;
    switch (groundTag)
    	{
            case TAG_OBJECT_GROUND:
            {
					runNormal();
                    break;
            }
            case TAG_OBJECT_BARNORMAL:
            case TAG_OBJECT_BARSLOPE:
            {
                float groundWidth = groundNode->getBoundingBox().getMaxX();
                tmp = 10;
				bool velocityCheck = this->mModel->getVelocityY() > tmp;
				bool positionCheck = std::abs(this->mModel->getPosX() - groundNode->getPosition().x) < groundWidth / 2;

				if (velocityCheck && positionCheck){
                        contact->SetEnabled(false);
				}
				else{
					runNormal();
				}
                break;
            }
            case TAG_OBJECT_BACK:
            {
				if (!isChangeDirection)
				{
					mModel->setDirection(-1);
					isChangeDirection = true;
				}
				
                break;
            }
			case TAG_OBJECT_END:
			{
				if (isChangeDirection)
				{
					isChangeDirection = false;
					mModel->setFinish(true);
				}
				break;
			}
			
            default:
                break;
    	}
}

void Runner::endCollideGround(){
	this->mModel->setState(PlayerState::ON_AIR);
	this->mModel->isMultiJump = false;
}


void Runner::EndContact(b2Node* node, b2Contact* contact){
	int targetTag = node->getTag();
	switch (targetTag)
	{
	case TAG_OBJECT_GROUND:{
							   this->endCollideGround();
							   break;
	}
	default:
		break;
	}
}

void Runner::runNormal(){
	this->mModel->setVelocityX(15.0f*this->mModel->getDirection());
	this->mModel->setState(PlayerState::ON_GROUND);
	this->mModel->isMultiJump = true;
}

void Runner::jump(){
	if (this->mModel->canJump())
		this->mModel->setVelocityY(this->mModel->getJumpSpeed());
}

