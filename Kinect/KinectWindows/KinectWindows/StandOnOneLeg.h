#pragma once
#include "Gesture.h"
class StandOnOneLeg :public Gesture
{
public:
	StandOnOneLeg();
	~StandOnOneLeg();

	bool checkForGesture();
};

