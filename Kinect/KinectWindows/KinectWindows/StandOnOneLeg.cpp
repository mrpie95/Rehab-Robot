#include "StandOnOneLeg.h"



StandOnOneLeg::StandOnOneLeg() : Gesture("Stand on one Leg")
{
}


StandOnOneLeg::~StandOnOneLeg()
{
}

bool StandOnOneLeg::checkForGesture()
{
	this->skeleton = skeleton;

	if (this->getLeftFootPos().y - 300.0f > this->getRightFootPos().y)
	{
		return true;
	}

	if (this->getRightFootPos().y - 300.0f > this->getLeftFootPos().y)
	{
		return true;

	}

	return false;
}
