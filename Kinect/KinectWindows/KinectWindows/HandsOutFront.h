#pragma once
#include "gestureInterface.h"
class HandsOutFront :public GestureInterface
{
public:
	HandsOutFront();
	~HandsOutFront();

	bool checkForGesture();
};

