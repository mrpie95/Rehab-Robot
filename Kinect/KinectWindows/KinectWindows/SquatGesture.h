#pragma once
#include "gestureInterface.h"


class SquatGesture :
	public GestureInterface
{
private:
	float angleOfSquat; //inDegrees

public:
	SquatGesture();
	~SquatGesture();

	bool checkForGesture() override;
	bool checkForDoingGesture() override;
	std::string print() override;
};

