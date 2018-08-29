#pragma once
#include <vector>
#include "gestureInterface.h"

class GestureRecEngine
{
private:
	std::vector<GestureInterface*> gestures;
public:
	GestureRecEngine();
	~GestureRecEngine();

	void addGesture(GestureInterface*);
	GestureInterface* checkForGesture(nite::Skeleton);
	std::vector<GestureInterface*> checkForDoingGestures(nite::Skeleton);
};

