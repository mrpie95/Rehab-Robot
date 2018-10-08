#include "StandOnOneLeg.h"
#include "INIHandler.h"


StandOnOneLeg::StandOnOneLeg() : Gesture("Stand on one Leg")
{
}


StandOnOneLeg::~StandOnOneLeg()
{
}

bool StandOnOneLeg::checkForGesture()
{

	float legDistance = INIHandler::getInstance().getValue<float>("fStandOnOneLegDistanceBetweenFeet");

	if (this->getLeftFootPos().y - legDistance > this->getRightFootPos().y)
	{
		return true;
	}

	if (this->getRightFootPos().y - legDistance > this->getLeftFootPos().y)
	{
		return true;

	}

	return false;
}
