#include "HandsOnHead.h"



HandsOnHead::HandsOnHead(nite::Skeleton skeleton): GestureInterface(skeleton)
{
}


HandsOnHead::~HandsOnHead()
{
}

bool HandsOnHead::checkForGesture()
{
	float LeftHandToHead = euclidDistance(this->getLeftHandPos(), this->getHeadPos());
	float RightHandToHead = euclidDistance(this->getRightHandPos(), this->getHeadPos());

	if (LeftHandToHead < 200.0f && RightHandToHead < 200.0f)
	{
		return true;
	}
	return false;
}
