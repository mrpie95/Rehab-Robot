#include <iostream>
#include "Gesture.h"

Gesture::Gesture()
{
}

bool Gesture::GestureMatched(const NUI_SKELETON_DATA & skel)
{
	
	for (int i = 0; i < NUI_SKELETON_POSITION_COUNT; i++) {
		skeletonPosition[i] = skel.SkeletonPositions[i];
	}

	if (skeletonPosition[NUI_SKELETON_POSITION_HAND_LEFT].y > skeletonPosition[NUI_SKELETON_POSITION_HEAD].y) {
		std::cout << "Your left hand is above your head";
	}
	return false;
}
