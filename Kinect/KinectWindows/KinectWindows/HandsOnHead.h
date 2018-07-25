#pragma once
#include "gestureInterface.h"

class HandsOnHead :public GestureInterface
{
public:
	HandsOnHead();
	~HandsOnHead();

	bool checkForGesture();
};

