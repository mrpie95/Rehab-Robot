#pragma once
#include "Gesture.h"
class HandsOutFront :public Gesture
{
public:
	HandsOutFront();
	~HandsOutFront();

	bool checkForGesture();
};

