#pragma once
#include "gestureInterface.h"

class HandsOnShoulders :public GestureInterface
{
public:
	HandsOnShoulders();
	~HandsOnShoulders();

	bool checkForGesture(nite::Skeleton skeleton);
};

