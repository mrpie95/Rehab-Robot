#pragma once
#include "Gesture.h"

class HandsOnShoulders :public Gesture
{
public:
	HandsOnShoulders();
	~HandsOnShoulders();

	bool checkForGesture();
};

