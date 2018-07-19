#include "HandsOnHips.h"



HandsOnHips::HandsOnHips(nite::Skeleton skel) : GestureInterface(skel)
{
}


HandsOnHips::~HandsOnHips()
{
}

bool HandsOnHips::checkForGesture()
{
	float leftHandToLeftHip = euclidDistance(this->getLeftHandPos(), this->getLeftHipPos()); 
	float rightHandToRightHip = euclidDistance(this->getRightHandPos(), this->getRightHipPos());

	if (leftHandToLeftHip < 200.0f && rightHandToRightHip < 200.0f)
	{
		return true;
	}


	return false;
}
