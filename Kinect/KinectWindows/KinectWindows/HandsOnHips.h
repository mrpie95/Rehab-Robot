#pragma once
#include "Gesture.h"
class HandsOnHips :public Gesture
{
public:
	HandsOnHips();
	~HandsOnHips();

	bool checkForGesture();
};

