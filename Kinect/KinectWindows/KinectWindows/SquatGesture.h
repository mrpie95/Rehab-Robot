#pragma once
#include "Gesture.h"


class SquatGesture :
	public Gesture
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

