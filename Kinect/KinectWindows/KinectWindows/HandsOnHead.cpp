#include "HandsOnHead.h"



HandsOnHead::HandsOnHead(): GestureInterface("Head")
{
}


HandsOnHead::~HandsOnHead()
{
}

bool HandsOnHead::checkForGesture(nite::Skeleton skeleton)
{
	this->skeleton = skeleton;
	float LeftHandToHead = euclidDistance3D(this->getLeftHandPos(), this->getHeadPos());
	float RightHandToHead = euclidDistance3D(this->getRightHandPos(), this->getHeadPos());

	if (LeftHandToHead < 200.0f && RightHandToHead < 200.0f)
	{
		return true;
	}
	return false;
}
