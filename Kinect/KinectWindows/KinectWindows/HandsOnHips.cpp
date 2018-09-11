#include "HandsOnHips.h"



HandsOnHips::HandsOnHips() : Gesture("Hands on hips")
{
}


HandsOnHips::~HandsOnHips()
{
}

bool HandsOnHips::checkForGesture()
{
	float leftHandToLeftHip = euclidDistance3D(this->getLeftHandPos(), this->getLeftHipPos()); 
	float rightHandToRightHip = euclidDistance3D(this->getRightHandPos(), this->getRightHipPos());

	if (leftHandToLeftHip < 200.0f && rightHandToRightHip < 200.0f)
	{
		return true;
	}


	return false;
}
