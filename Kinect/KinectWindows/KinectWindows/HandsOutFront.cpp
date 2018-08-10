#include "HandsOutFront.h"



HandsOutFront::HandsOutFront() : GestureInterface("Hands Out Front")
{
}


HandsOutFront::~HandsOutFront()
{
}

bool HandsOutFront::checkForGesture()
{
	if (this->getLeftHandPos().z < this->getTorsoPos().z - 400.0f)
		if (this->getRightHandPos().z < this->getTorsoPos().z - 400.0f)
			return true;




	return false;
}
