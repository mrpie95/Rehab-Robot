#include "SquatGesture.h"
#include <math.h>
#include "INIHandler.h"

#define PI 3.14159265
#define ANGLE_FOR_SQUAT_DOING 70

SquatGesture::SquatGesture() :Gesture("Squat")
{
	angleOfSquat = 180.0;
}


SquatGesture::~SquatGesture()
{
}

bool SquatGesture::checkForGesture()
{
	angleOfSquat = asin( (this->getLeftHipPos().y - this->getLeftKneePos().y) / euclidDistance3D(this->getLeftKneePos(), this->getLeftHipPos())) * 180.0/PI;
	angleOfSquat += asin((this->getRightHipPos().y - this->getRightKneePos().y) / euclidDistance3D(this->getRightKneePos(), this->getRightHipPos())) * 180.0 / PI;
	angleOfSquat /= 2;

	float angle = INIHandler::getInstance().getValue<float>("fAngleOfSquat");

	return angleOfSquat <= angle;
}

bool SquatGesture::checkForDoingGesture()
{
	//todo: remove this
	return true;
	return angleOfSquat <= ANGLE_FOR_SQUAT_DOING;
}

std::string SquatGesture::print()
{
	return std::string("Angle Of Squat: "+ std::to_string(angleOfSquat));
}
