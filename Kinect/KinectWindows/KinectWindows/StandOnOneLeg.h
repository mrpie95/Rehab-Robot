#pragma once
#include "gestureInterface.h"
class StandOnOneLeg :public GestureInterface
{
public:
	StandOnOneLeg();
	~StandOnOneLeg();

	bool checkForGesture();
};

