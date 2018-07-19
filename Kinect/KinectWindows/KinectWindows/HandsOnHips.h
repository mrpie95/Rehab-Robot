#pragma once
#include "gestureInterface.h"
class HandsOnHips :public GestureInterface
{
public:
	HandsOnHips(nite::Skeleton skel);
	~HandsOnHips();

	bool checkForGesture();
};

