#include "HandsOnShoulders.h"



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

	if (leftHandToLeftShoulder < 200.0f && rightHandToRightShoulder < 200.0f)
	{
		return true;
	}


	return false;
}
