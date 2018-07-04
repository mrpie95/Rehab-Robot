#pragma once

#include "Gesture.h"
#include <vector>

class Motion {
private:
	std::vector<Gesture> gestureList;

public:
	Motion();

	void ProcessGesture(const NUI_SKELETON_DATA & skel);
};