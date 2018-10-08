#include "HandsOnHips.h"
#include "INIHandler.h"


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

	float left = INIHandler::getInstance().getValue<float>("fLeftHandToLeftHipDistance");
	float right = INIHandler::getInstance().getValue<float>("fRightHandToRightHipDistance");

	if (leftHandToLeftHip < left && rightHandToRightHip < right)
	{
		return true;
	}


	return false;
}
