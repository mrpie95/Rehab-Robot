#pragma once

#ifndef GESTURE_H
#define GESTURE_H

#include <Windows.h>
#include "NuiApi.h"

class Gesture {
private:
	Vector4 skeletonPosition[NUI_SKELETON_POSITION_COUNT];

public:
	Gesture();

	bool GestureMatched(const NUI_SKELETON_DATA & skel);
};

#endif