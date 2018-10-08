#include "HandsOnShoulders.h"
#include "INIHandler.h"


HandsOnShoulders::HandsOnShoulders() : Gesture("Hands on shoulders")
{
}


HandsOnShoulders::~HandsOnShoulders()
{
}

bool HandsOnShoulders::checkForGesture()
{
	float leftHandToLeftShoulder = euclidDistance3D(this->getLeftHandPos(), this->getLeftShoulderPos());
	float rightHandToRightShoulder = euclidDistance3D(this->getRightHandPos(), this->getRightShoulderPos());

	float left = INIHandler::getInstance().getValue<float>("fLeftHandToLeftShoulderDistance");
	float right = INIHandler::getInstance().getValue<float>("fRightHandToRightShoulderDistance");

	if (leftHandToLeftShoulder < left && rightHandToRightShoulder < right)
	{
		return true;
	}


	return false;
}
