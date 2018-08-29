#include "SquatGesture.h"
#include <math.h>

#define PI 3.14159265
#define ANGLE_FOR_SQUAT_COMPLETION 100
#define ANGLE_FOR_SQUAT_DOING 150

SquatGesture::SquatGesture() :GestureInterface("Squat")
{
	angleOfSquat = 180.0;
}


SquatGesture::~SquatGesture()
{
}

bool SquatGesture::checkForGesture()
{
	angleOfSquat = asin( (this->getLeftHipPos().y - this->getLeftKneePos().y) / euclidDistance3D(this->getLeftKneePos(), this->getLeftHipPos())) * 180.0/PI;
	angleOfSquat += 90.0;

	return angleOfSquat <= ANGLE_FOR_SQUAT_COMPLETION;
}

bool SquatGesture::checkForDoingGesture()
{
	return angleOfSquat <= ANGLE_FOR_SQUAT_DOING;
}

std::string SquatGesture::print()
{
	return std::string("Angle Of Squat: "+ std::to_string(angleOfSquat));
}
