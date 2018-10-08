#include "HandsOnHead.h"
#include "INIHandler.h"


HandsOnHead::HandsOnHead(): Gesture("Hands on head")
{
}


HandsOnHead::~HandsOnHead()
{
}

bool HandsOnHead::checkForGesture()
{
	float LeftHandToHead = euclidDistance3D(this->getLeftHandPos(), this->getHeadPos());
	float RightHandToHead = euclidDistance3D(this->getRightHandPos(), this->getHeadPos());

	float left = INIHandler::getInstance().getValue<float>("fHandsOnHeadDistanceLeftHand");
	float right = INIHandler::getInstance().getValue<float>("fHandsOnHeadDistanceRightHand");

	if (LeftHandToHead < left && RightHandToHead < right)
	{
		return true;
	}
	return false;
}
