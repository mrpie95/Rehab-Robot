#include "HandsOutFront.h"
#include "INIHandler.h"


HandsOutFront::HandsOutFront() : Gesture("Hands Out Front")
{
}


HandsOutFront::~HandsOutFront()
{
}

bool HandsOutFront::checkForGesture()
{
	float left = INIHandler::getInstance().getValue<float>("fHandOutFrontLeftHandDistanceFromChest");
	float right = INIHandler::getInstance().getValue<float>("fHandOutFrontRightHandDistanceFromChest");

	if (this->getLeftHandPos().z < this->getTorsoPos().z - left)
		if (this->getRightHandPos().z < this->getTorsoPos().z - right)
			return true;




	return false;
}
