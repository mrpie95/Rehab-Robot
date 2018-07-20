#include "HandsOnShoulders.h"



HandsOnShoulders::HandsOnShoulders() : GestureInterface("Shoulders")
{
}


HandsOnShoulders::~HandsOnShoulders()
{
}

bool HandsOnShoulders::checkForGesture(nite::Skeleton skeleton)
{
	this->skeleton = skeleton;
	float leftHandToLeftShoulder = euclidDistance(this->getLeftHandPos(), this->getLeftShoulderPos());
	float rightHandToRightShoulder = euclidDistance(this->getRightHandPos(), this->getRightShoulderPos());

	if (leftHandToLeftShoulder < 200.0f && rightHandToRightShoulder < 200.0f)
	{
		return true;
	}


	return false;
}
