#include "Motion.h"

Motion::Motion()
{
	Gesture gesture1;
	gestureList.push_back(gesture1);
}

void Motion::ProcessGesture(const NUI_SKELETON_DATA & skel) {
	for (Gesture g : gestureList) {
		g.GestureMatched(skel);
	}
	

	return;
}