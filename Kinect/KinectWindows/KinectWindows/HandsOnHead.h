#pragma once
#include "Gesture.h"

class HandsOnHead :public Gesture
{
public:
	HandsOnHead();
	~HandsOnHead();

	bool checkForGesture() override;
};

