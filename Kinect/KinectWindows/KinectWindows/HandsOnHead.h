#pragma once
#include "gestureInterface.h"

class HandsOnHead :public GestureInterface
{
public:
	HandsOnHead(nite::Skeleton skelton);
	~HandsOnHead();

	bool checkForGesture();
};

