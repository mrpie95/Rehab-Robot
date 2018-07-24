#include "HandsOnHips.h"



HandsOnHips::HandsOnHips() : GestureInterface("Hips")
{
}


HandsOnHips::~HandsOnHips()
{
}

bool HandsOnHips::checkForGesture(nite::Skeleton skeleton)
{
	this->skeleton = skeleton;
	float leftHandToLeftHip = euclidDistance3D(this->getLeftHandPos(), this->getLeftHipPos()); 
	float rightHandToRightHip = euclidDistance3D(this->getRightHandPos(), this->getRightHipPos());

	if (leftHandToLeftHip < 200.0f && rightHandToRightHip < 200.0f)
	{
		return true;
	}


	return false;
}
